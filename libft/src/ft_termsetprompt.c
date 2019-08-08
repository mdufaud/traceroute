/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termsetprompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 19:19:57 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/23 19:21:49 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

void	ft_termsetprompt(char *s, t_term *term)
{
	if (term->prompt)
	{
		term->prompt_len = 0;
		ft_strdel(&term->prompt);
	}
	term->prompt = ft_strdup(s);
	term->prompt_len = ft_strlen(s);
}
