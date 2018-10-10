/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 20:31:37 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 12:15:46 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <unistd.h>
#include <stdio.h> // remove plz

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
		return (-1);
	if (IS_SIGN(*str))
		sign = *str++ == '-' ? -1 : 1;
	if (!IS_DIGIT(*str))
		return (-1);
	while (*str && IS_DIGIT(*str))
	{
		output *= 10;
		output += (int)(*str++ - '0');
	}
	output *= sign;
	*out = (output);
	return (0);
}

void	ft_print_map(t_parser_state *state)
{
	int			line;
	int			i;
	t_line		*node;

	line = 0;
	while (line < state->line_number)
	{
		node = state->head_list[line].line;
		i = 0;
		while (node)
		{
			while (i < node->index)
			{
				write(1, &g_info.obstacle, 1);
				i++;
			}
			while (i < node->index + node->length)
			{
				write(1, &g_info.empty, 1);
				i++;
			}
			node = node->next;
		}
		while (i < g_info.width)
		{
			write(1, &g_info.obstacle, 1);
			i++;
		}
		write(1, "\n", 1);
		line++;
	}
}
