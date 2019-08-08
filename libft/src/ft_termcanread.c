/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcanread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:23:05 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/24 16:23:23 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

int		ft_termcanread(t_term *term)
{
	if ((term->code & FT_TERM_READ)
			&& !(term->code & FT_TERM_ERROR)
			&& !(term->code & FT_TERM_EXIT))
		return (1);
	return (0);
}
