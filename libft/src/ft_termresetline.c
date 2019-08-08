/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termresetline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 18:11:11 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/26 17:35:29 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

void	ft_termresetline(t_term *term, char *s)
{
	ft_termhome(term);
	ft_termexec("cd");
	term->pos = ft_strlen(s);
	ft_termprompt(term);
	ft_putcstr(s, term->str_color);
}
