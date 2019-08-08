/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 20:47:42 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/23 20:55:59 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

void	ft_keyend(t_term *term)
{
	int		i;
	int		j;
	int		bl;

	ft_keyhome(term);
	bl = ft_strlen(term->buffer);
	i = (bl + term->prompt_len - 1) / term->w_col;
	j = (bl + term->prompt_len - 1) % term->w_col;
	if (term->pos < bl)
	{
		while (i)
		{
			ft_termexec("do");
			i--;
		}
		tputs(tgoto(tgetstr("ch", NULL), 0, j + 1), 1, ft_termputs);
	}
	term->pos = bl;
}
