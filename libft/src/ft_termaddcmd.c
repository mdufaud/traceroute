/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termaddcmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:55:19 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/24 17:53:29 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

void	ft_termaddcmd(t_term *term, char *cmds)
{
	int		i;
	char	**split;
	t_dlist	*new;

	i = 0;
	if (!(split = ft_strsplit(cmds, ' ')))
		return ;
	ft_dlstfirst(&term->cmds);
	while (split[i])
	{
		new = ft_dlstnew(split[i], ft_strlen(split[i]) + 1);
		ft_dlstadd(&term->cmds, new);
		i++;
	}
	ft_tabfree(&split);
}
