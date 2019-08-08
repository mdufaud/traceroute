/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termhome.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 20:57:22 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/23 20:58:01 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

void	ft_termhome(t_term *term)
{
	int		l;
	int		pl;

	pl = term->prompt_len;
	l = (term->pos + pl) / term->w_col;
	if (term->pos >= 0)
	{
		while (l)
		{
			ft_termexec("up");
			l--;
		}
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_termputs);
	}
	term->pos = 0;
}
