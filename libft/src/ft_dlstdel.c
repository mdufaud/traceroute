/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:27:27 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/23 17:02:21 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		default_del(void *c, size_t s)
{
	ft_bzero(c, s);
	ft_memdel(&c);
}

void			ft_dlstdel(t_dlist **alst, void (*del)(void *, size_t))
{
	t_dlist	*tmp;

	ft_dlstfirst(alst);
	while (*alst)
	{
		tmp = (*alst);
		(*alst) = (*alst)->next;
		if (del)
			(*del)(tmp->content, tmp->content_size);
		else
			default_del(tmp->content, tmp->content_size);
		free(tmp);
	}
}
