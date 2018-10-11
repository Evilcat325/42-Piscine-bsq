# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seli <seli@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/09 16:23:54 by seli              #+#    #+#              #
#    Updated: 2018/10/10 23:33:48 by seli             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(IDIR)

IDIR = ./includes
SRCDIR = srcs

SOURCES = ft_main.c ft_data.c ft_stdio.c ft_string.c \
			ft_solve_bsq.c ft_bsq_util.c \
			ft_bsq_parser.c ft_square.c ft_error.c
SOURCES := $(SOURCES:%=$(SRCDIR)/%)


all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) -O3 -o $(NAME) $(SOURCES)

clean:

fclean:
	@/bin/rm -f $(NAME)

re: fclean all
