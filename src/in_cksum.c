/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_cksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/05/04 22:42:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traceroute.h"

unsigned short	in_cksum(unsigned short *addr, int len)
{
	register int		sum;
	u_short				answer;
	register u_short	*w;
	register int		nleft;

	sum = 0;
	answer = 0;
	w = addr;
	nleft = len;
	while (nleft > 1)
	{
	  sum += *w++;
	  nleft -= 2;
	}
	if (nleft == 1)
	{
	  *((u_char *)&answer) = *(u_char *)w;
	  sum += answer;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = (short)~sum;
	return (answer);
}

unsigned short	p_cksum(char *src, char *dst, char *buff, unsigned short len_udp)
{
	unsigned short		prot_udp;
	unsigned short		word;
	unsigned long		sum;
	unsigned short		i;
	unsigned short		padd;

	sum = 0;
	i = 0;
	padd = 0;
	prot_udp = 17;
	while (i < len_udp + padd)
	{
		word = ((buff[i] << 8) & 0xFF00) + (buff[i + 1] & 0xFF);
		sum += word;
		i += 2;
	}
	i = 0;
	while (i < 4)
	{
		word = ((src[i] << 8) & 0xFF00) + (src[i + 1] & 0xFF);
		sum += word;
		i += 2;
	}
	i = 0;
	while (i < 4)
	{
		word = ((dst[i] << 8) & 0xFF00) + (dst[i + 1] & 0xFF);
		sum += word;
		i += 2;
	}
	sum = sum + prot_udp + len_udp;
	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);
	sum = ~sum;
	return (sum);
}

/*
unsigned short	p_cksum(struct ip *ip, unsigned short *data, int len)
{
	struct ipovly	ipo;
	unsigned short	sumh;
	unsigned short	sumd;
	unsigned long	sumt;

	ipo.ih_pr = ip->ip_p;
	ipo.ih_len = htons(len);
	ipo.ih_src = ip->ip_src;
	ipo.ih_dst = ip->ip_dst;

	sumh = in_cksum((unsigned short *)&ipo, sizeof(ipo));
	sumd = in_cksum((unsigned short *)data, len);
	sumt = (sumh << 16) | (sumd);
	return (~in_cksum((unsigned short *)&sumt, sizeof(sumt));
}*/
