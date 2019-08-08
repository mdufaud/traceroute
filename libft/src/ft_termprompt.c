/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termprompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 19:21:57 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/26 16:58:06 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"
#include <unistd.h>

void	ft_termprompt(t_term *term)
{
	if (!isatty(1) || !ft_termexist())
		return ;
	if (term->prompt)
		ft_putcstr(term->prompt, term->prompt_color);
}
