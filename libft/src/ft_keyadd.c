/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 18:58:34 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/26 17:45:40 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

static void		jump_line(t_term *term)
{
	if ((term->pos + term->prompt_len + 1) % term->w_col == 0)
	{
		ft_termexec("do");
		ft_termexec("ch");
	}
}

void			ft_keyadd(char *key, t_term *term)
{
	char	*tmp;

	if (key[0] < 32 || ft_strlen(term->buffer) == FT_TERM_BUFFSIZE - 1)
		return ;
	if (!term->buffer[term->pos])
	{
		term->buffer[term->pos] = key[0];
		ft_putcchar(term->buffer[term->pos], term->str_color);
		jump_line(term);
	}
	else
	{
		tmp = term->buffer + term->pos;
		ft_memmove(tmp + 1, tmp, ft_strlen(tmp));
		term->buffer[term->pos] = key[0];
		ft_putcchar(term->buffer[term->pos], term->str_color);
		jump_line(term);
		ft_termrewrite(tmp + 1, term->str_color);
	}
	++term->pos;
}
