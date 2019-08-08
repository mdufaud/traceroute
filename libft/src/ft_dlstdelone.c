/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:30:15 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/23 17:18:19 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void		default_del(void *c, size_t s)
{
	ft_bzero(c, s);
	ft_memdel(&c);
}

void			ft_dlstdelone(t_dlist **alst, void (*del)(void *, size_t))
{
	t_dlist		*tmp;

	if (del)
		(*del)((*alst)->content, (*alst)->content_size);
	else
		default_del((*alst)->content, (*alst)->content_size);
	tmp = (*alst)->prev;
	if ((*alst)->prev)
		(*alst)->prev->next = (*alst)->next;
	if ((*alst)->next)
		(*alst)->next->prev = tmp;
	tmp = (*alst)->next ? (*alst)->next : (*alst)->prev;
	ft_bzero(*alst, sizeof(t_dlist));
	free(*alst);
	*alst = tmp;
}
