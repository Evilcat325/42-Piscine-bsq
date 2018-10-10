/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print_map_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 21:31:51 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 00:31:21 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_bsq.h"
#include <stdio.h>

void	ft_print_map_list(t_head *head)
{
	t_line		*node;

	node = NULL;
	while (head)
	{
		node = head->line;
		while (node)
		{
			printf("index: %d, length: %d |", node->index, node->length);
			node = node->next;
		}
		printf("\n");
		head = head->next;
	}
}
