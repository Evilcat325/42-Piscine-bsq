/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 21:31:51 by seli              #+#    #+#             */
/*   Updated: 2018/10/09 21:36:04 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_test.h"

void	ft_print_map_list(t_head *head)
{
	t_line		*node;

	while (head)
	{
		node = head->line;
		while (node)
		{
			printf("index: %d, length: %d | ", node->index, node->length);
			node = node->next;
		}
		printf("\n");
	}
}
