/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 17:43:53 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/26 17:57:36 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"
#include <stdlib.h>

static void		set_term_struct(t_term *term)
{
	term->pos = 0;
	term->prompt = NULL;
	term->prompt_len = 0;
	term->w_row = 0;
	term->w_col = 0;
	term->hist = NULL;
	term->comp = NULL;
	term->cmds = NULL;
	term->options = NULL;
	term->str_color = none;
	term->prompt_color = none;
}

static char		*get_env(char **environ)
{
	int		i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "TERM=", 5) == 0)
			return (environ[i] + 5);
		i++;
	}
	return (NULL);
}

static t_term	*term_exit(t_term *new)
{
	if (new)
		free(new);
	ft_termexit();
	return (NULL);
}

t_term			*ft_termnew(int opt, char **environ)
{
	t_term	*new;
	char	buffer[FT_TERM_BUFFSIZE];

	if ((tgetent(buffer, get_env(environ)) < 1))
		return (NULL);
	ft_terminit();
	if (!ft_termexist())
		return (NULL);
	if (!(new = (t_term *)malloc(sizeof(t_term))))
		return (term_exit(NULL));
	set_term_struct(new);
	new->opt = opt;
	ft_termsize(new);
	if (!(new->buffer = ft_strnew(FT_TERM_BUFFSIZE)))
		return (term_exit(new));
	if (!(new->comp_buffer = ft_strnew(FT_TERM_BUFFSIZE)))
	{
		free(new->buffer);
		return (term_exit(new));
	}
	return (new);
}
