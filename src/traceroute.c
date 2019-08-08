/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

int			get_src(t_env *env)
{
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct sockaddr		*addr;
	struct sockaddr_in	*addr_in;
	socklen_t			len;

	addr = NULL;
	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = env->family;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, "3490", &hints, &res))
		return (error("Could not get source"));
	while (res)
	{
		addr = res->ai_addr;
		len = res->ai_addrlen;
		res = res->ai_next;
	}
	env->src_sockaddr.sa_family = addr->sa_family;
	ft_memcpy(env->src_sockaddr.sa_data, addr->sa_data, 14);
	env->src_addr_len = len;
	freeaddrinfo(res);
	addr_in = (struct sockaddr_in *)&env->src_sockaddr;
	if (!(env->src_addr = ft_strnew(BUFF_SIZE)))
		return (error("Could not allocate source addr"));
	if (!inet_pton(env->family, env->src_addr, &addr_in->sin_addr))
	{
		ft_strcat(env->src_addr, SRC_ADDR);
		if (!inet_pton(env->family, env->src_addr, &addr_in->sin_addr))
			return (error("Could not find src addr"));
	}
	return (0);
}

static int	send_next_ttl_packet(t_env *env, struct timeval *before, struct timeval *timeout)
{
	int		sent;

	env->ttl++;
	env->ttl_changed = 1;
	if (env->ttl >= env->hops + 1)
	{
		env->loop = 0;
		return (1);
	}
	if (env->stat.n_sent > 0)
		printf("\n");
	env->recv = 0;
	env->sent = 0;
	env->send_next = 0;
	env->last_recv = 0;
	gettimeofday(before, NULL);
	timeout->tv_usec = !env->wait ? 200000 : 0;
	timeout->tv_sec = env->wait;
	env->print_addr = 1;
	sent = send_packet(env);
	if (sent > 0)
	{
		printf(" %d\t", env->ttl);
		return (0);
	}
	return (1);
}

static int	send_next_packet(t_env *env, struct timeval *before)
{
	if (!env->last_recv)
		printf("* ");
	if (env->sent == env->n_queries)
	{
		if (env->reached)
		{
			env->loop = 0;
			return (1);
		}	
		env->send_next = 1;
	}
	else
	{
		gettimeofday(before, NULL);
		if (send_packet(env) < 0)
			return (1);
	}
	return (0);
}

int			traceroute(t_env *env)
{
	struct timeval		timeout;
	struct timeval		before;
	struct timeval		after;
	int					ret;

	gettimeofday(&env->stat.start_time, NULL);
	if ((env->socket = socket(env->family, env->sock_type, env->protocol)) == -1)
		return (error("Socket error"));
	env->loop = 42;
	env->addr_in.sin_family = AF_INET;
	env->addr_in.sin_port = htons(env->port);
	inet_pton(AF_INET, env->host, &env->addr_in.sin_addr);
	/*
	if (get_src(env))
		return (1);
	if (ARG_CHECK(env->arg, "-U"))
	{
		struct sockaddr_in	sin;

		int broadcast = 1;
		sin.sin_family = AF_INET;
		sin.sin_port = 0;
		sin.sin_addr.s_addr = INADDR_ANY;

		if (setsockopt(env->socket, SOL_SOCKET,
			SO_BROADCAST, &broadcast, sizeof(broadcast)) == -1)
			return (error("Could not broadcast"));
		if (bind(env->socket, ((struct sockaddr *)&sin), sizeof(sin)) < 0)
			return (error("Could not bind"));
	}
	*/
	while (env->loop)
	{
		FD_ZERO(&env->fd_read);
		FD_SET(env->socket, &env->fd_read);
		if (env->send_next && send_next_ttl_packet(env, &before, &timeout))
			break ;
		if ((ret = select(env->socket + 1, &env->fd_read, NULL, NULL, &timeout)) < 0)
			return (error("Select error"));
		gettimeofday(&after, NULL);
		if (FD_ISSET(env->socket, &env->fd_read))
			recv_packet(env, before, after);
		if ((env->last_recv || !ret) && send_next_packet(env, &before))
			break ;
	}
	close(env->socket);
	printf("\n");
	return (0);
}
