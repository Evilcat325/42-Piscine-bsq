/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 20:31:37 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 15:57:37 by seli             ###   ########.fr       */
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

void	ft_print_map(t_parser_state *state)
{
	int			line;
	int			i;
	t_spacenode	*node;
	// char		*empty;
	// char		*obstcale;

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
		write(1, "\n", 1);
		line++;
	}
}
