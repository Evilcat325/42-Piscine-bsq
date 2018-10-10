# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/09 16:23:54 by seli              #+#    #+#              #
#    Updated: 2018/10/10 03:20:17 by nkirkby          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(IDIR)

IDIR = ./includes
SRCDIR = srcs

SOURCES = ft_main.c ft_data.c ft_stdio.c ft_string.c \
			ft_solve_bsq.c ft_bsq_util.c
SOURCES := $(SOURCES:%=$(SRCDIR)/%)


all: $(NAME)

$(NAME):
	@$(CC) $(CFLAGS) -o $(NAME) $(SOURCES) ft_error.c

debug:
	@$(CC) $(CFLAGS) -o $(NAME) $(SOURCES) .debug/ft_error.c -g 

clean:

fclean:
	@/bin/rm -f $(NAME)
	@/bin/rm -rf $(NAME).dSYM

re: fclean all
