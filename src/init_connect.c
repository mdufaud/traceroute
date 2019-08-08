/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_connect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 16:36:12 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/16 19:30:08 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

static char	*get_host(t_arg *args)
{
	int		i;

	i = 1;
	while (i < args->argc)
	{
		if (args->argv[i][0] == '-')
			i += 2;
		if (i < args->argc && args->argv[i][0] != '-')
			return (ft_strdup(args->argv[i]));
		i++;
	}
	return (ft_strdup(args->argv[args->argc - 1]));
}

int			init_connect(t_env *env)
{
	int					mask;
	char				*host;
	char				*canonname;
	struct sockaddr_in	addr_in;
	struct sockaddr_in6	addr_in6;

	canonname = NULL;
	host = NULL;
	mask = AUTH_IPV4;
	if (!env->host && !(env->host = get_host(env->arg)))
		return (error("no address specified"));
	env->family = 0;
	if (inet_pton(AF_INET6, env->host, &addr_in6.sin6_addr))
	{
		env->family = AF_INET6;
		if (!(mask & AUTH_IPV6))
			return (error("IPV6 not implemented"));
	}
	else if (inet_pton(AF_INET, env->host, &addr_in.sin_addr))
		env->family = AF_INET;
	if (env->family)
	{
		if (env->enable_dns)
			get_hostname(env->family, env->host, &canonname, NULL);
		env->canonname = !canonname ? env->host : canonname;
	}
	else
	{
		if (env->sock_type == SOCK_RAW)
			mask |= HINT_SOCK_RAW;
		if (env->protocol == IPPROTO_UDP)
			mask |= HINT_UDP;
		if (env->protocol == IPPROTO_ICMP)
			mask |= HINT_ICMP;
		env->family = interrogate_dns(env->host, &host, mask);
		env->canonname = env->host;
		env->host = host;
	}
	if (env->family <= 0)
		return (error_s("unkown host ", !env->canonname ? env->host : env->canonname));
	printf("Traceroute to %s (%s), %d hops max, %d byte packets\n", env->canonname, env->host, env->hops, env->packet_bytes);
	return (0);
}
