/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keytab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 16:24:34 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/26 17:08:10 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"
#include <stdlib.h>

static void		set_comp(t_term *term)
{
	char	*tmp;

	if (!term->comp || !term->comp->content_size)
		return ;
	if (!(tmp = ft_strjoin(term->buffer, term->comp->content)))
		return ;
	ft_strcpy(term->comp_buffer, tmp);
	free(tmp);
	ft_termresetline(term, term->comp_buffer);
}

static char		*get_word(char *s, int index)
{
	int		beg;
	int		end;
	int		i;

	i = 0;
	if (index < 0)
		return (NULL);
	while (index + i >= 0 && s[index + i] && !ft_isspace(s[index + i]))
		i--;
	beg = index + i;
	if (ft_isspace(s[beg]))
		beg += 1;
	i = 0;
	while (s[index + i] && !ft_isspace(s[index + i]))
		i++;
	end = index + i;
	if (end - beg <= 0)
		return (NULL);
	return (ft_strsub(s, beg, end - beg));
}

static void		create_lst(t_term *term, char **stab)
{
	int		i;
	int		len;
	int		stab_len;
	t_dlist	*new;
	char	*word;

	i = 0;
	word = get_word(term->buffer, term->pos - 1);
	len = word ? ft_strlen(word) : 0;
	while (stab[i])
	{
		if (!len || (!ft_strncmp(stab[i], word, len)
					&& (stab_len = ft_strlen(stab[i])) - len > 0))
		{
			new = ft_dlstnew(stab[i] + len,
							stab_len - len);
			ft_dlstadd(&term->comp, new);
		}
		i++;
	}
	free(word);
}

static void		complete_options(t_term *term, char *cmd)
{
	int		len;
	int		i;
	char	**stab;

	if (!cmd)
		return ;
	len = ft_strlen(term->buffer);
	i = 0;
	if (ft_hashfind(&term->options, cmd))
	{
		stab = term->options->value;
		create_lst(term, stab);
	}
}

static void		complete_cmds(t_term *term, char *cmd)
{
	int		len;
	t_dlist	*new;
	t_dlist	*first;

	len = ft_strlen(cmd);
	ft_dlstfirst(&term->cmds);
	first = term->cmds;
	while (term->cmds)
	{
		if (!ft_strncmp(term->cmds->content, cmd, len))
		{
			new = ft_dlstnew(term->cmds->content + len,
							term->cmds->content_size - len);
			ft_dlstadd(&term->comp, new);
		}
		term->cmds = term->cmds->next;
	}
	term->cmds = first;
}

void			ft_keytab(t_term *term)
{
	char	**split;

	split = NULL;
	if (term->pos <= 0)
		return ;
	if (!term->comp)
	{
		if (!(split = ft_strsplit(term->buffer, ' ')))
			return ;
		if (ft_tablen(split) == 1
				&& (term->pos > 0 && term->buffer[term->pos - 1] != ' ')
				&& term->cmds)
			complete_cmds(term, split[0]);
		else if (term->options && !term->buffer[term->pos])
			complete_options(term, split[0]);
	}
	else
	{
		if (term->comp->next)
			term->comp = term->comp->next;
		else
			ft_dlstfirst(&term->comp);
	}
	set_comp(term);
	if (split)
		ft_tabfree(&split);
}
