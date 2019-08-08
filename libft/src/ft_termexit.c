/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termexit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 17:36:37 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/23 20:22:47 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"
#include <unistd.h>
#include <fcntl.h>

void		ft_termexit(void)
{
	struct termios		term;
	int					fd;

	fd = open("/dev/tty", O_RDONLY);
	fd = fd < 0 ? 0 : fd;
	tcgetattr(fd, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(fd, TCSANOW, &term);
	if (fd > 0)
		close(fd);
}
