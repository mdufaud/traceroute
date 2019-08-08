/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:23:35 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/23 21:53:09 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_dlist		*ft_dlstnew(void const *content, size_t content_size)
{
	t_dlist	*new;

	if (!(new = (t_dlist *)malloc(sizeof(t_dlist))))
		return (NULL);
	new->content = NULL;
	new->content_size = 0;
	new->next = NULL;
	new->prev = NULL;
	if (content)
	{
		if (!(new->content = ft_memalloc(content_size)))
		{
			free(new);
			return (NULL);
		}
		new->content = ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	return (new);
}
