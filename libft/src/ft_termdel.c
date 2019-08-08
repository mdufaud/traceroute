/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 18:47:47 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/24 19:56:14 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"
#include <stdlib.h>

void	ft_termdel(t_term **term)
{
	ft_strdel(&(*term)->buffer);
	ft_strdel(&(*term)->comp_buffer);
	if ((*term)->prompt)
		ft_strdel(&(*term)->prompt);
	if ((*term)->hist)
		ft_dlstdel(&(*term)->hist, NULL);
	if ((*term)->comp)
		ft_dlstdel(&(*term)->comp, NULL);
	if ((*term)->cmds)
		ft_dlstdel(&(*term)->cmds, NULL);
	if ((*term)->options)
		ft_hashfree(&(*term)->options);
	ft_bzero(*term, sizeof(t_term));
	free(*term);
	*term = NULL;
	ft_termexit();
}
