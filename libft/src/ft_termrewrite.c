/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termrewrite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 20:27:37 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/26 17:35:15 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

void	ft_termrewrite(char *s, t_color color)
{
	ft_termexec("cd");
	ft_termexec("sc");
	ft_putcstr(s, color);
	ft_termexec("rc");
}
