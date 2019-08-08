/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hostname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

static int	get_ipv4(char *ip, char **hostname, char **service_name)
{
	struct sockaddr_in	sa;
	int					ret;
	char				host[1024];
	char				service[20];

	sa.sin_family = AF_INET;
	sa.sin_port = htons(3490);
	inet_pton(AF_INET, ip, &sa.sin_addr);
	if ((ret = getnameinfo((struct sockaddr *)&sa, sizeof(sa),
							host, sizeof(host), service, sizeof(service), NI_NAMEREQD)))
		return (ret);
	*hostname = ft_strdup(host);
	if (service_name)
		*service_name = ft_strdup(service);
	return (0);
}

static int	get_ipv6(char *ip, char **hostname, char **service_name)
{
	struct sockaddr_in6	sa;
	int					ret;
	char				host[1024];
	char				service[20];

	sa.sin6_family = AF_INET6;
	sa.sin6_port = htons(3490);
	inet_pton(AF_INET, ip, &sa.sin6_addr);
	if ((ret = getnameinfo((struct sockaddr *)&sa, sizeof(sa),
							host, sizeof(host), service, sizeof(service), 0)))
		return (ret);
	*hostname = ft_strdup(host);
	if (service_name)
		*service_name = ft_strdup(service);
	return (0);
}

int			get_hostname(int family, char *ip, char **hostname, char **service_name)
{
	int		ret;

	ret = 1;
	*hostname = NULL;
	if (service_name)
		*service_name = NULL;
	if (family == AF_INET)
		ret = get_ipv4(ip, hostname, service_name);
	else if (family == AF_INET6)
		ret = get_ipv6(ip, hostname, service_name);
	return (ret);
}
