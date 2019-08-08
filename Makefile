# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/27 14:59:24 by mdufaud           #+#    #+#              #
#    Updated: 2016/02/16 19:08:14 by mdufaud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OS := $(shell uname)

ifeq ($(OS),Linux)
SHELL := /bin/bash
ECHO := echo -e
else
SHELL := /bin/sh
ECHO := echo
endif

NAME = ft_traceroute
PATH_SRC = src
PATH_OBJ = obj
PATH_INCLUDES = include
CFLAGS = gcc -Wall -Wextra -Werror
OFLAGS = -I libft/includes/. -I $(PATH_INCLUDES)
LFLAGS = -L libft -lft
LIB = libft/libft.a
MKLIB = make -C libft
SRC = main.c\
	  error.c\
	  init_connect.c\
	  get_hostname.c\
	  in_cksum.c\
	  interrogate_dns.c\
	  send.c\
	  recv.c\
	  traceroute.c

OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

NO_PATH_INCLUDES = traceroute.h

INCLUDES = $(patsubst %.h, $(PATH_INCLUDES)/%.h, $(NO_PATH_INCLUDES))

all: $(NAME)

$(LIB):
	@$(MKLIB)

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/, %.c) $(INCLUDES)
	@mkdir -p $(PATH_OBJ)
	@$(CFLAGS) $(OFLAGS) -o $@ -c $<

$(NAME): $(LIB) $(OBJ)
	@$(ECHO) "\033[32m[ $(NAME) objects done ]\033[00m"
	@$(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)
	@$(ECHO) "\033[32m[ $(NAME) compiled ]\033[00m"

lib: $(LIB) $(NAME)
	@$(ECHO) "\033[32m[ Library done && $(NAME) compiled ]\033[00m"

clean:
	@$(MKLIB) clean
	@rm -f $(OBJ)
	@$(ECHO) "\033[31m[ $(NAME) : objects deleted ]\033[00m"

fclean: clean
	@$(MKLIB) fclean
	@rm -f $(NAME)
	@$(ECHO) "\033[31m[ $(NAME) : ./$(NAME) deleted ]\033[00m"

re: fclean all

.PHONY: fclean re clean all lib
