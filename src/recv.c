/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

static void			print_rtt(struct timeval *old, struct timeval *new)
{
	double	dt;
	int		precis;

	dt = (double)(new->tv_sec - old->tv_sec) * 1000.0
		+ (double)(new->tv_usec - old->tv_usec) / 1000.0;
	if (dt >= 1000.0)
		precis = 0;
	else if (dt >= 100.0)
		precis = 1;
	else if (dt >= 10.0)
		precis = 2;
	else
		precis = 3;
	printf("%.*f ms ", precis, dt);
}

static void		print_addr(t_env *env, char *ip_str)
{
	char					*canonname;

	canonname = NULL;
	if (env->print_addr)
	{
		if (env->enable_dns)
			get_hostname(env->family, ip_str, &canonname, NULL);
		if (!canonname)
			canonname = (char *)ip_str;
		if (ARG_CHECK(env->arg,"-n"))
			printf("%s  ", ip_str);
		else
			printf("%s (%s):  ", canonname, ip_str);
		env->print_addr = 0;
	}
	env->recv++;
	env->stat.n_recv++;
	env->last_recv = 1;
}

static int		check_route(t_env *env, unsigned long n)
{
	int		i;
	int		max;

	i = 0;
	max = env->ttl + 1 > env->hops ? env->hops : env->ttl + 1;
	while (i < max)
	{
		if (env->addrs_route[i] > 0 && env->addrs_route[i] == n)
			return (0);
		i++;
	}
	return (1);
}

int				recv_packet(t_env *env, struct timeval old, struct timeval new)
{
	struct sockaddr			addr;
	socklen_t				addr_len;
	char					buf[BUFF_SIZE];
	char					ip_str[INET6_ADDRSTRLEN];
	struct ip				*ip;
	struct icmp				*icmp;
	struct udphdr			*udp;
	int						iphdr_len;
	int						ret;

	ft_bzero(ip_str, INET6_ADDRSTRLEN);
	addr_len = INET6_ADDRSTRLEN;
	if ((ret = recvfrom(env->socket, buf, BUFF_SIZE, 0, &addr, &addr_len)) <= 0)
		return (1);
	if (!inet_ntop(addr.sa_family,
			&((struct sockaddr_in *)&addr)->sin_addr,
			ip_str, INET6_ADDRSTRLEN))
		return (1);
	if (env->ttl_changed && check_route(env, ((struct sockaddr_in *)&addr)->sin_addr.s_addr))
	{
		env->addrs_route[env->ttl] = ((struct sockaddr_in *)&addr)->sin_addr.s_addr;
		env->ttl_changed = 0;
		env->print_addr = 1;
	}
	else if (env->ttl_changed && env->addrs_route[env->ttl - 1] == ((struct sockaddr_in *)&addr)->sin_addr.s_addr)
		return (2);
	else if (!env->ttl_changed && env->addrs_route[env->ttl] != ((struct sockaddr_in *)&addr)->sin_addr.s_addr)
		return (3);
	ip = (struct ip *)buf;
	iphdr_len = ip->ip_hl << 2;
	icmp = (struct icmp *)(buf + iphdr_len);
	udp = (struct udphdr *)(buf + iphdr_len);
	if (ip->ip_p == IPPROTO_ICMP
		&& ((icmp->icmp_type == ICMP_TIME_EXCEEDED
			&& icmp->icmp_code == ICMP_TIMXCEED_INTRANS)
			|| icmp->icmp_type == ICMP_ECHOREPLY))
	{
		if (icmp->icmp_type == ICMP_TIME_EXCEEDED
			&& icmp->icmp_code == ICMP_TIMXCEED_INTRANS)
		{
			ip = &icmp->icmp_ip;
			iphdr_len = ip->ip_hl << 2;
			icmp = (struct icmp *)((char *)ip + iphdr_len);
		}
		if (icmp->icmp_id == env->pid)
		{
			if (icmp->icmp_type == ICMP_ECHOREPLY
				 && ft_strequ(ip_str, env->host))
				env->reached = 1;
			print_addr(env, ip_str);
			print_rtt(&old, &new);
			env->last_recv = 1;
		}
	}
	else if (ip->ip_p == IPPROTO_UDP)
	{
		(void)udp;
		print_addr(env, ip_str);
		print_rtt(&old, &new);
		env->last_recv = 1;
	}
	return (0);
}
