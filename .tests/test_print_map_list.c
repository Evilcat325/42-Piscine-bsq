/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print_map_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 21:31:51 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 11:08:46 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_bsq.h"
#include <stdio.h>
#include <unistd.h>

void	ft_print_map_list(t_parser_state *state)
{
	int			line;
	t_line		*node;

	line = 0;
	while (line < state->line_number)
	{
		node = state->head_list[line].line;
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
		printf("\n");
		line++;
	}
}