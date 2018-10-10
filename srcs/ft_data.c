/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 18:33:34 by seli              #+#    #+#             */
/*   Updated: 2018/10/09 22:36:39 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_data.h"

t_head		*create_head_node(t_head *prev)
{
	t_head	*curr;

	if ((curr = malloc(sizeof(t_head))) == NULL)
		return (NULL);
	if (prev)
		prev->next = curr;
	curr->prev = prev;
	curr->next = NULL;
	curr->line = NULL;
	curr->search = NULL;
	return (curr);
}

t_line		*create_line_node(t_line *prev, int position, int empty_len)
{
	t_line	*curr;

	if ((curr = malloc(sizeof(t_line))) == NULL)
		return (NULL);
	if (prev)
		prev->next = curr;
	curr->index = position;
	curr->length = empty_len;
	return (curr);
}
