/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termgetkey.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 17:28:42 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/24 18:12:57 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

static const t_termkey	g_tabkey[] = {
	{"\x0A\0\0\0\0", &ft_keyreturn},
	{"\x04\0\0\0\0", &ft_keyexit},
	{"\x7f\0\0\0\0", &ft_keybackdel},
	{"\x1b\x5b\x33\x7e\0", &ft_keydel},
	{"\x1b\x5b\x41\0\0", &ft_keyarrowup},
	{"\x1b\x5b\x42\0\0", &ft_keyarrowdown},
	{"\x1b\x5b\x43\0\0", &ft_keyarrowright},
	{"\x1b\x5b\x44\0\0", &ft_keyarrowleft},
	{"\x1b\x5b\x48\0\0", &ft_keyhome},
	{"\x1b\x5b\x46\0\0", &ft_keyend},
	{"\x09\0\0\0\0", &ft_keytab},
	{NULL, NULL}
};

static void	switch_buffer(t_term *term)
{
	if (term->comp_buffer[0])
	{
		ft_strcpy(term->buffer, term->comp_buffer);
		ft_termresetline(term, term->buffer);
		ft_bzero(term->comp_buffer, FT_TERM_BUFFSIZE);
	}
}

int			ft_termgetkey(char *key, t_term *term)
{
	int			i;

	i = 0;
	if (ft_memcmp(key, "\x09\0\0\0\0", 4) != 0)
	{
		ft_dlstdel(&term->comp, NULL);
		switch_buffer(term);
	}
	while (g_tabkey[i].keycode)
	{
		if (ft_memcmp(key, g_tabkey[i].keycode, 4) == 0)
		{
			g_tabkey[i].f(term);
			return (1);
		}
		i++;
	}
	ft_keyadd(key, term);
	ft_dlstfirst(&term->hist);
	return (0);
}
