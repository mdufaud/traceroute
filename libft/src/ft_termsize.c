/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 17:39:56 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/23 19:44:05 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void	ft_termsize(t_term *term)
{
	struct winsize	term_size;
	int				fd;

	fd = open("/dev/tty", O_RDONLY);
	fd = fd < 0 ? 0 : fd;
	ioctl(fd, TIOCGWINSZ, &term_size);
	term->w_col = term_size.ws_col;
	term->w_row = term_size.ws_row;
	if (fd > 0)
		close(fd);
}
