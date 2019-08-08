/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyarrows.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 20:28:54 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/26 17:56:25 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_termcaps.h"

void	ft_keyarrowright(t_term *term)
{
	if (term->pos < (int)ft_strlen(term->buffer))
	{
		term->pos++;
		if ((term->pos + term->prompt_len) % term->w_col == 0)
		{
			ft_termexec("do");
			ft_termexec("ch");
		}
		else
			ft_termexec("nd");
	}
}

void	ft_keyarrowleft(t_term *term)
{
	int		tmp;

	if (term->pos > 0)
	{
		tmp = (term->pos + term->prompt_len) >= term->w_col ?
			term->prompt_len : 0;
		if ((term->pos + tmp) % term->w_col == 0)
		{
			ft_termexec("up");
			tputs(tgoto(tgetstr("ch", NULL), 0, term->w_col - 1),
					1, ft_termputs);
		}
		else
			tputs(tgoto(tgetstr("le", NULL), 0, 0), 1, ft_termputs);
		term->pos -= 1;
	}
}

void	ft_keyarrowdown(t_term *term)
{
	int		cmp;

	if (!term->hist)
		return ;
	cmp = ft_strcmp(term->buffer, term->hist->content);
	if (term->hist)
	{
		ft_termhome(term);
		ft_termexec("cd");
		ft_bzero(term->buffer, FT_TERM_BUFFSIZE);
		term->pos = 0;
		if (!cmp && term->hist->prev)
		{
			term->hist = term->hist->prev;
			term->pos = term->hist->content_size - 1;
			ft_memcpy(term->buffer, term->hist->content, term->pos);
		}
		ft_termprompt(term);
		ft_putcstr(term->buffer, term->str_color);
	}
}

void	ft_keyarrowup(t_term *term)
{
	if (!term->hist)
		return ;
	if (!ft_strcmp(term->buffer, term->hist->content) && term->hist->next)
		term->hist = term->hist->next;
	if (term->hist)
	{
		ft_termhome(term);
		ft_termexec("cd");
		ft_bzero(term->buffer, FT_TERM_BUFFSIZE);
		term->pos = term->hist->content_size - 1;
		ft_memcpy(term->buffer, term->hist->content, term->pos);
		ft_termprompt(term);
		ft_putcstr(term->buffer, term->str_color);
	}
}
