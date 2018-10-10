# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seli <seli@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/09 16:23:54 by seli              #+#    #+#              #
#    Updated: 2018/10/09 22:54:05 by seli             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(IDIR)

IDIR = ./includes
SRCDIR = srcs

SOURCES = ft_main.c ft_data.c ft_stdio.c ft_string.c ft_test.c \
			ft_solve_bsq.c
SOURCES := $(SOURCES:%=$(SRCDIR)/%)


all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) -o $(NAME) $(SOURCES)

debug:
	@$(CC) $(CFLAGS) -o $(NAME) $(SOURCES) -g

clean:

fclean:
	@/bin/rm -f $(NAME)
	@/bin/rm -rf $(NAME).dSYM

re: fclean all
