/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyhome.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 20:47:34 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/23 20:51:48 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

void	ft_keyhome(t_term *term)
{
	int		l;
	int		pl;

	pl = term->prompt_len;
	l = (term->pos + pl) / term->w_col;
	if (term->pos > 0)
	{
		while (l)
		{
			ft_termexec("up");
			l--;
		}
		tputs(tgoto(tgetstr("ch", NULL), 0, pl), 1, ft_termputs);
	}
	term->pos = 0;
}
