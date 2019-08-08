/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 16:19:44 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/16 19:12:34 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACEROUTE_H
# define TRACEROUTE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>/////
# include <netdb.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <sys/select.h>
# include <netinet/udp.h>

# include <errno.h> ////////////

# define ENV_PORT 32768 + 666
# define SRC_PORT 6666
# define DST_PORT 8622
# define SRC_ADDR "127.0.0.1"
# define IOV_DATA_LEN 1024
# define MSG_DATA_LEN 4096
# define BUFF_SIZE 4096
# define AUTH_IPV4 (2 << 1)
# define AUTH_IPV6 (2 << 2)
# define AUTH_IPVALL ((2 << 1) | (2 << 2))
# define HINT_SOCK_RAW (2 << 3)
# define HINT_UDP (2 << 4)
# define HINT_ICMP (2 << 5)

typedef struct s_pseudo_header
{
	u_int32_t	source_address;
	u_int32_t	dest_address;
	u_int8_t	placeholder;
	u_int8_t	protocol;
	u_int16_t	udp_length;
}				t_pseudo_header;

typedef struct			s_stat
{
	int					n_recv;
	int					n_sent;
	struct timeval		start_time;
}						t_stat;

typedef struct			s_env
{
	t_arg				*arg;
	char				*host;
	struct sockaddr_in	addr_in;
	struct sockaddr		src_sockaddr;
	char				*src_addr;
	socklen_t			src_addr_len;
	char				*canonname;
	unsigned long		*addrs_route;
	int					protocol;
	int					sock_type;
	int					socket;
	int					pid;
	int					family;
	int					port;
	int					ttl;
	int					packet_size;
	int					n_queries;
	int					packet_bytes;
	int					hops;
	int					wait;
	int					reached;
	int					loop;
	int					send_next;
	int					sent;
	int					recv;
	int					packets_lost;
	int					last_recv;
	int					enable_dns;
	int					print_addr;
	int					ttl_changed;
	fd_set				fd_read;
	t_stat				stat;
}						t_env;

int				init_connect(t_env *env);
int				interrogate_dns(char *host, char **ip, int flag);
int				error(char *err);
int				error_s(char *err, char *s);
int				get_hostname(int family, char *ip, char **hostname, char **service_name);
unsigned short	in_cksum(unsigned short *addr, int len);
unsigned short	p_cksum(char *src, char *dst, char *buff, unsigned short len_udp);
int				traceroute(t_env *env);
int				send_packet(t_env *env);
int				recv_packet(t_env *env, struct timeval old, struct timeval new);

#endif
