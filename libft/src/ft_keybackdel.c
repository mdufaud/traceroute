/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keybackdel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 20:25:20 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/26 17:04:56 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

void		ft_keybackdel(t_term *term)
{
	char	*tmp;

	if (term->pos > 0)
	{
		ft_keyarrowleft(term);
		tmp = term->buffer + term->pos;
		ft_memmove(tmp, tmp + 1, ft_strlen(tmp) + 1);
		ft_termexec("dc");
		ft_termrewrite(tmp, term->str_color);
	}
}
