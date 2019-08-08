/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interrogate_dns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

static void	fill_hints(struct addrinfo *hints, int flag)
{
	ft_bzero(hints, sizeof(struct addrinfo));
	hints->ai_family = AF_UNSPEC;
	hints->ai_socktype = flag & HINT_SOCK_RAW ? SOCK_RAW : SOCK_DGRAM;
	hints->ai_protocol = flag & HINT_ICMP ? IPPROTO_ICMP : IPPROTO_UDP;
	hints->ai_flags = AI_CANONNAME;
	hints->ai_canonname = NULL;
	hints->ai_addr = NULL;
	hints->ai_next = NULL;

}

static void	fill_ipv6(struct addrinfo *results, char **ip, int *family)
{
	struct sockaddr_in6	*addr_in6;
	char				str6[INET6_ADDRSTRLEN];

	*family = results->ai_family;
	addr_in6 = (struct sockaddr_in6 *)results->ai_addr;
	*ip = ft_strdup(inet_ntop(AF_INET6, &(addr_in6->sin6_addr), str6, INET6_ADDRSTRLEN));
}

static void	fill_ipv4(struct addrinfo *results, char **ip, int *family)
{
	struct sockaddr_in	*addr_in;
	char				str[INET_ADDRSTRLEN];

	*family = results->ai_family;
	addr_in = (struct sockaddr_in *)results->ai_addr;
	*ip = ft_strdup(inet_ntop(AF_INET, &(addr_in->sin_addr), str, INET_ADDRSTRLEN));
}

int			interrogate_dns(char *host, char **ip, int flag)
{
	int					family;
	struct addrinfo		hints;
	struct addrinfo		*results;
	struct addrinfo		*res;
	int					ret;

	fill_hints(&hints, flag);
	if ((ret = getaddrinfo(host, NULL, &hints, &results)))
		return (-1);
	if (!results)
		return (-2);
	res = results;
	family = 0;
	*ip = NULL;
	while (results)
	{
		if ((flag & AUTH_IPV6) && (results->ai_family == AF_INET6))
			fill_ipv6(results, ip, &family);
		else if ((flag & AUTH_IPV4) && (results->ai_family == AF_INET))
			fill_ipv4(results, ip, &family);
		results = results->ai_next;
	}
	freeaddrinfo(res);
	return (family);
}
