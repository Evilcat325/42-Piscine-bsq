/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 20:31:37 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 22:48:47 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> //

#define IS_DIGIT(X) (X >= '0' && X <= '9')
#define IS_SIGN(X) (X == '+' || X == '-')

/*
**	This version of atoi mutates a pointed-to integer
**	Returns 0 if succesful, other if the argument is invalid.
*/

int		ft_atoi_ptr(char *str, int *out)
{
	int	output;
	int	sign;

	output = 0;
	sign = 1;
	while (*str == ' ')
		str++;
	if (!(IS_DIGIT(*str) || IS_SIGN(*str)))
		return (ft_map_error("atoi: char after space is not number or sign"));
	if (IS_SIGN(*str))
		sign = *str++ == '-' ? -1 : 1;
	while (*str)
	{
		if (!IS_DIGIT(*str))
			return (ft_map_error("atoi: non number char in string"));
		output *= 10;
		output += (int)(*str++ - '0');
	}
	output *= sign;
	*out = (output);
	return (SUCCESS);
}

int		ft_is_full(t_square *biggest_square, int row, t_spacenode *node)
{
	if (row <= biggest_square->row &&
		row > biggest_square->row - biggest_square->size &&
		LEFT_LIMIT(node) <= biggest_square->col &&
		biggest_square->col < RIGHT_LIMIT(node))
		return (TRUE);
	return (FALSE);
}

void	ft_full_node(t_square *biggest_square, t_spacenode *node,
						t_string_state *strings)
{
	if (node->index == biggest_square->col)
	{
		write(1, strings->square, biggest_square->size);
		write(1, strings->empty, node->length - biggest_square->size);
	}
	else
	{
		write(1, strings->empty, biggest_square->col - node->index);
		write(1, strings->square, biggest_square->size);
		if (biggest_square->col + biggest_square->size < RIGHT_LIMIT(node))
			write(1, strings->empty,
				RIGHT_LIMIT(node) - biggest_square->col - biggest_square->size);
	}
}

void	ft_print_solution(t_parser_state *state, t_square *biggest_square)
{
	int				line;
	t_string_state	strings;

	ft_initialize_string(&strings, state, biggest_square);
	line = 0;
	while (line < state->line_number)
	{
		if (!&state->lines[line])
			write(1, strings.obstacle, state->file_info.width);
		else
			ft_print_line(&strings, state, biggest_square, line);
		line++;
		write(1, "\n", 1);
	}
	free(strings.empty);
	free(strings.obstacle);
	free(strings.square);
}

void	ft_print_line(t_string_state *strings, t_parser_state *state,
						t_square *biggest_square, int line)
{
	t_spacenode		*node;

	node = state->lines[line].nodes;
	if (node && node->index != 0)
		write(1, strings->obstacle, node->index);
	while (node)
	{
		if (ft_is_full(biggest_square, line, node))
			ft_full_node(biggest_square, node, strings);
		else
			write(1, strings->empty, node->length);
		if (node->next)
			write(1, strings->obstacle,
				LEFT_LIMIT(node->next) - RIGHT_LIMIT(node));
		else if (!node->next && RIGHT_LIMIT(node) < state->file_info.width)
			write(1, strings->obstacle,
				state->file_info.width - RIGHT_LIMIT(node));
		node = node->next;
	}
}
