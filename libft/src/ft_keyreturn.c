/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyreturn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 18:53:50 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/23 22:00:10 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

void		ft_keyreturn(t_term *term)
{
	t_dlist		*new;
	int			len;

	if (!(term->opt & FT_TERM_NOHISTORY) && (len = ft_strlen(term->buffer)))
	{
		ft_dlstfirst(&term->hist);
		new = ft_dlstnew(term->buffer, len + 1);
		ft_dlstadd(&term->hist, new);
	}
	ft_putchar('\n');
	term->code -= FT_TERM_READ;
}
