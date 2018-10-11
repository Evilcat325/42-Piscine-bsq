/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print_map_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 21:31:51 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 21:12:06 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_bsq.h"
#include <stdio.h>
#include <unistd.h>

void	ft_print_map_list(t_parser_state *state)
{
	int				line;
	t_spacenode		*node;

	line = 0;
	while (line < state->line_number)
	{
		node = state->lines[line].nodes;
		while (node)
		{
			printf("index: %d, length: %d |", node->index, node->length);
			node = node->next;
		}
		printf("\n");
		line++;
	}
}

void	ft_print_map(t_parser_state *state)
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