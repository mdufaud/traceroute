/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termgnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 15:57:51 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/24 16:23:35 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int			ft_termgnl(char **line, t_term *term)
{
	char	key[4];
	int		ret;

	term->code = FT_TERM_READ;
	while (ft_termcanread(term) && (ret = ft_termread(key, term)) > 0)
		ft_termgetkey(key, term);
	*line = ft_strdup(term->buffer);
	ft_bzero(term->buffer, FT_TERM_BUFFSIZE);
	term->pos = 0;
	if ((term->code & FT_TERM_EXIT))
		return (0);
	if ((term->code & FT_TERM_ERROR))
		return (-1);
	return (ret);
}
