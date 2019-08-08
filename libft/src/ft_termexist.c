/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termexist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 17:37:30 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/23 20:18:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

int			ft_termexist(void)
{
	struct termios		term;

	tcgetattr(0, &term);
	if (!(term.c_lflag & (ICANON | ECHO)))
		return (1);
	return (0);
}
