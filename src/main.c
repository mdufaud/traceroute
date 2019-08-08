/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 16:19:42 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/16 19:08:00 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

static int	usage(void)
{
	ft_putendl("Usage: sudo ./ft_traceroute [-f first_ttl] [-m max_ttl] \
[-q nqueries] [-w waittime] [-n no dns resolution]");
	return (1);
}

static void	init_env(t_env *env)
{
	env->packet_bytes = 60;
	env->hops = 30;
	env->wait = 5;
	env->enable_dns = 1;
	env->n_queries = 3;
	env->stat.n_recv = 0;
	env->stat.n_sent = 0;
	env->reached = 0;
	env->ttl = 0;
	env->send_next = 1;
	env->last_recv = 0;
	env->pid = getpid();
	env->host = NULL;
	env->canonname = NULL;
	//env->port = 32768 + 666;
	env->port = ENV_PORT;
	env->print_addr = 0;
	env->protocol = IPPROTO_ICMP;
	env->sock_type = SOCK_RAW;
}

static int	allocate_route(t_env *env)
{
	unsigned long	i;

	i = 0;
	if (!(env->addrs_route = malloc(sizeof(unsigned long) * env->hops)))
		return (error("Could not allocate routes"));
	while ((int)i < env->hops)
	{
		env->addrs_route[i] = 0;
		i++;
	}
	return (0);
}

static int	parse_args(t_env *env)
{
	char	*str;

	if (ARG_CHECK(env->arg, "-m"))
	{
		if (!(str = ARG_FETCH(env->arg, "-m")))
			return (error("No argument for max_ttl"));
		if (!ft_strisdigit(str))
			return (error("Argument for max_ttl is not a number"));
		env->hops = ft_atoi(str);
		free(str);
		if (env->hops <= 0)
			return (error("Argument for max_ttl must be positive"));
	}
	if (ARG_CHECK(env->arg, "-q"))
	{
		if (!(str = ARG_FETCH(env->arg, "-q")))
			return (error("No argument for queries"));
		if (!ft_strisdigit(str))
			return (error("Argument for queries is not a number"));
		env->n_queries = ft_atoi(str);
		free(str);
		if (env->n_queries <= 0)
			return (error("Argument for queries must be positive"));
		if (env->n_queries > 10)
			return (error("Can't have more than 10 queries per hop"));
	}
	if (ARG_CHECK(env->arg, "-w"))
	{
		if (!(str = ARG_FETCH(env->arg, "-w")))
			return (error("No argument for wait time"));
		if (!ft_strisdigit(str))
			return (error("Argument for wait time is not a number"));
		env->wait = ft_atoi(str);
		free(str);
		if (env->wait < 0)
			return (error("Argument for wait time can't be negative"));
	}
	if (ARG_CHECK(env->arg, "-f"))
	{
		if (!(str = ARG_FETCH(env->arg, "-f")))
			return (error("No argument for first ttl"));
		if (!ft_strisdigit(str))
			return (error("Argument for first ttl is not a number"));
		env->ttl = ft_atoi(str);
		free(str);
		if (env->ttl <= 0)
			return (error("Argument for first ttl must be positive"));
		env->ttl -= 1;
	}
	if (ARG_CHECK(env->arg, "-n"))
		env->enable_dns = 0;
	if (ARG_CHECK(env->arg, "-U"))
	{
		env->protocol = IPPROTO_UDP;
		env->sock_type = SOCK_RAW;
	}
	if (env->sock_type == SOCK_RAW && getuid())
		return (error("You must be root to open raw sockets"));
	return (allocate_route(env));
}

int			main(int argc, char **argv)
{
	t_arg	*arg;
	t_env	env;

	if (argc < 2)
		return (usage());
	if (!(arg = ft_argnew(argc, argv, "-h -m -q -w -f -n")))
		return (error("could not allocate arguments"));
	if (arg->check(arg, "-h"))
		return (usage());
	arg->get_error(arg);
	if (arg->error)
		return (error(arg->error));
	env.arg = arg;
	init_env(&env);
	if (parse_args(&env))
		return (1);
	if (init_connect(&env))
		return (1);
	if (traceroute(&env))
		return (1);
	return (0);
}
