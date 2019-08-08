/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 19:32:25 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/24 16:15:11 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int			ft_termread(char *key, t_term *term)
{
	int		ret;

	ft_bzero(key, 4);
	ret = read(0, key, 4);
	if (ret < 0)
		term->code += FT_TERM_ERROR;
	if (ret == 0)
		term->code += FT_TERM_EXIT;
	return (ret);
}
