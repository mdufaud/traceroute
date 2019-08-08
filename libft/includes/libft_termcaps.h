/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_termcaps.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:18:30 by mdufaud           #+#    #+#             */
/*   Updated: 2016/02/26 17:57:32 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_TERMCAPS_H
# define LIBFT_TERMCAPS_H

# include "libft.h"
# include <termios.h>
# include <termcap.h>
# include <curses.h>
# include <term.h>

# define FT_TERM_BUFFSIZE 2048
# define FT_TERM_NOHISTORY (2 << 0)
# define FT_TERM_PROMPT (2 << 1)
# define FT_TERM_STR (2 << 2)
# define FT_TERM_READ (2 << 1)
# define FT_TERM_EXIT (2 << 2)
# define FT_TERM_ERROR (2 << 3)

typedef struct		s_term
{
	char			*prompt;
	char			*buffer;
	char			*comp_buffer;
	int				opt;
	int				pos;
	int				prompt_len;
	int				w_row;
	int				w_col;
	int				code;
	t_color			prompt_color;
	t_color			str_color;
	t_dlist			*hist;
	t_dlist			*comp;
	t_dlist			*cmds;
	t_hash			*options;
}					t_term;

typedef struct		s_termkey
{
	char			*keycode;
	void			(*f)(t_term *);
}					t_termkey;

t_term				*ft_termnew(int opt, char **environ);
void				ft_terminit(void);
void				ft_termsize(t_term *term);
void				ft_termexit(void);
int					ft_termexist(void);
int					ft_termgetkey(char *key, t_term *term);
void				ft_termprompt(t_term *term);
void				ft_termsetprompt(char *s, t_term *term);
void				ft_termdel(t_term **term);
void				ft_keyadd(char *key, t_term *term);
void				ft_termexec(char *s);
int					ft_termread(char *key, t_term *term);
int					ft_termgnl(char **line, t_term *term);
int					ft_termputs(int c);
void				ft_termhome(t_term *term);
int					ft_termcanread(t_term *term);
void				ft_termaddcmd(t_term *term, char *cmds);
void				ft_termresetline(t_term *term, char *s);
void				ft_termaddoptions(t_term *term, t_hash *hash);
void				ft_termrewrite(char *s, t_color color);
void				ft_termsetcolor(t_term *term, int opt, t_color color);

void				ft_keyreturn(t_term *term);
void				ft_keyhome(t_term *term);
void				ft_keyend(t_term *term);
void				ft_keytab(t_term *term);
void				ft_keyexit(t_term *term);
void				ft_keybackdel(t_term *term);
void				ft_keydel(t_term *term);
void				ft_keyarrowright(t_term *term);
void				ft_keyarrowleft(t_term *term);
void				ft_keyarrowup(t_term *term);
void				ft_keyarrowdown(t_term *term);

#endif
