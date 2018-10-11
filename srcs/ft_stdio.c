/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 20:31:37 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 21:50:26 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <unistd.h>

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

int		is_full(t_square *biggest_square, int row, int col)
{
	if (row <= biggest_square->row &&
		row > biggest_square->row - biggest_square->size &&
		col >= biggest_square->col &&
		col < biggest_square->col + biggest_square->size)
		return (1);
	return (0);
}

void	ft_print_solution(t_parser_state *state, t_square *biggest_square)
{
	int				line;
	t_string_state	strings;

	ft_initialize_string(&strings, state, biggest_square);
	line = 0;
	while (line < state->line_number)
	{
		ft_print_line(&strings, state, biggest_square, line);
		line++;
	}
}

void	ft_print_line(t_string_state *strings, t_parser_state *state,
						t_square *biggest_square, int line)
{
	t_spacenode		*node;

	UNUSED(biggest_square);
	if (!&state->lines[line])
		write(1, strings->obstacle, state->file_info.width);
	else
	{
		node = state->lines[line].nodes;
		if (node->index != 0)
			write(1, strings->obstacle, node->index);
		while (node)
		{
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
	write(1, "\n", 1);
}
