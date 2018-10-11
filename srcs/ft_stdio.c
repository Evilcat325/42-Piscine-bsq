/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 20:31:37 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 21:05:25 by nkirkby          ###   ########.fr       */
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
	int			line;
	int			i;
	t_spacenode	*node;

	line = 0;
	while (line < state->line_number)
	{
		node = state->lines[line].nodes;
		i = 0;
		while (node)
		{
			while (i < node->index)
			{
				write(1, &state->file_info.obstacle, 1);
				i++;
			}
			while (i < node->index + node->length)
			{
				if (is_full(biggest_square, line, i))
					write(1, &state->file_info.full, 1);
				else
					write(1, &state->file_info.empty, 1);
				i++;
			}
			node = node->next;
		}
		while (i < state->file_info.width)
		{
			write(1, &state->file_info.obstacle, 1);
			i++;
		}
		if (line < state->line_number - 1)
			write(1, "\n", 1);
		line++;
	}
}
