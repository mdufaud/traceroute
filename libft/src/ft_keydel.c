/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keydel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 20:41:34 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/26 17:05:21 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

void		ft_keydel(t_term *term)
{
	char	*tmp;

	if (term->pos < (int)ft_strlen(term->buffer))
	{
		tmp = term->buffer + term->pos;
		ft_memmove(tmp, tmp + 1, ft_strlen(tmp) + 1);
		ft_termrewrite(tmp, term->str_color);
	}
}
