/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

static int		forge_icmp_packet(t_env *env, char *buf)
{
	struct icmp	*icmp;
	int			size;

	icmp = (struct icmp *)buf;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = ICMP_ECHOREPLY;
	icmp->icmp_id = env->pid;
	icmp->icmp_seq = env->stat.n_sent;
	size = ICMP_MINLEN + 56;
	icmp->icmp_cksum = in_cksum((unsigned short *)icmp, size);
	env->packet_size = size;
	return (size);
}

void			fill_iph(t_env *env, struct iphdr *ip)
{
	ip->ihl = 5;
	ip->version = 4;
	ip->tos = 0;
	ip->tot_len = sizeof(ip) + sizeof(struct udphdr) + sizeof("hello");
	ip->id = htonl(env->pid);
	ip->frag_off = 0;
	ip->ttl = env->ttl;
	ip->protocol = IPPROTO_UDP;
	ip->check = 0;
	ip->saddr = ((struct sockaddr_in *)&env->src_sockaddr)->sin_addr.s_addr;
	ip->daddr = env->addr_in.sin_addr.s_addr;
}

void			fill_udp(t_env *env, struct udphdr *udp, int len)
{
	(void)env;
	//udp->source = htons(env->pid);
	udp->source = htons(SRC_PORT);
	//udp->dest = htons(env->port + env->stat.n_sent);
	udp->dest = htons(DST_PORT);
	udp->len = htons(sizeof(struct udphdr) + len);
	udp->check = 0;
}

void			fill_psh(t_env *env, t_pseudo_header *psh, struct iphdr *ip, int len)
{
	psh->source_address = ip->saddr;
	psh->dest_address = env->addr_in.sin_addr.s_addr;
	psh->protocol = IPPROTO_UDP;
	psh->placeholder = 0;
	psh->udp_length = htons(sizeof(struct udphdr) + len);
}

int				forge_udp_packet(t_env *env, char *buf)
{
	/*
	(void)env;
	ft_strcat(buf, "hello");
	return (ft_strlen(buf));
	*/
	
	struct udphdr	*udp;

	udp = (struct udphdr *)buf;
	//udp->source = htons(env->pid);
	//udp->dest = htons(env->port + env->stat.n_sent);
	udp->source = htons(SRC_PORT);
	udp->dest = htons(DST_PORT);
	env->packet_size = sizeof(struct udphdr) + 52;
	udp->len = env->packet_size;
	udp->check = in_cksum((unsigned short *)udp, env->packet_size);
	return (env->packet_size);

	/*
	struct iphdr	*ip;
	struct udphdr	*udp;
	char			*data;
	char			pseudogram[BUFF_SIZE];
	int				psize;
	t_pseudo_header	psh;
	char			payload[BUFF_SIZE];
	int				payload_len;

	ip = (struct iphdr *)buf;
	udp = (struct udphdr *)(buf + sizeof(struct ip));
	data = buf + sizeof(struct iphdr) + sizeof(struct udphdr);
	ft_bzero(payload, BUFF_SIZE);
	ft_strcpy(payload, "hello laskd;alksldka;sldka;sdkasd");
	payload_len = ft_strlen(payload);
	ft_strcpy(data, payload);

	fill_iph(env, ip);
	ip->check = in_cksum((unsigned short *)buf, ip->tot_len);
	env->packet_size = ip->tot_len;
	fill_udp(env, udp, payload_len);
	fill_psh(env, &psh, ip, payload_len);

	psize = sizeof(struct s_pseudo_header) + sizeof(struct udphdr) + payload_len;
	ft_bzero(pseudogram, BUFF_SIZE);
	ft_memcpy(pseudogram, (char *)&psh, sizeof(struct s_pseudo_header));
	ft_memcpy(pseudogram + sizeof(struct s_pseudo_header), udp,
							sizeof(struct udphdr) + payload_len);
	udp->check = in_cksum((unsigned short *)pseudogram, psize);
	return (ip->tot_len);
	*/
}

static int		make_send(t_env *env, char *buf)
{
	int					size;
	int					sent;

	if (ARG_CHECK(env->arg, "-U"))
	{
		struct udphdr	*udp;

		size = forge_udp_packet(env, buf);
		udp = (struct udphdr *)(buf + sizeof(struct iphdr));
		(void)udp;
	}
	else if (env->protocol == IPPROTO_ICMP)
	{
		size = forge_icmp_packet(env, buf);
		size = sizeof(struct icmp);
	}
	sent = sendto(env->socket, buf, size, 0,
					(struct sockaddr *)&env->addr_in,
					sizeof(struct sockaddr));
	return (sent);
}

int				send_packet(t_env *env)
{
	char				buf[BUFF_SIZE];
	int					ret;

	if (env->sent == env->n_queries)
		return (1);
	if ((setsockopt(env->socket, SOL_IP, IP_TTL, &env->ttl, sizeof(env->ttl))) == -1)
		return (error("Setting socket opt"));
	ft_bzero(buf, BUFF_SIZE);
	ret = make_send(env, buf);
	if (ret < 0)
		return (error("Invalid argument") * -1);
	env->stat.n_sent++;
	env->sent++;
	env->last_recv = 0;
	return (ret);
}
