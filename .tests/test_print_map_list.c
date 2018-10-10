/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print_map_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 21:31:51 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 11:10:36 by nkirkby          ###   ########.fr       */
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
