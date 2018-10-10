/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 18:33:34 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 02:58:12 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <stdlib.h>

void	ft_initialize_parser_state(t_parser_state *state)
{
	state->buf_i = 0;
	state->position = 0;
	state->break_position = 0;
	state->break_in_line = FALSE;
	state->line_number = 0;
	state->curr_node = NULL;
}

void		ft_initialize_new_line(t_parser_state *state)
{
	state->position = 0;
	state->break_position = 0;
	state->curr_node = 0;
	state->head_list[state->line_number].line = NULL;
	state->head_list[state->line_number].search = NULL;
}

t_line		*create_line_node(t_line **prev, int position, int empty_len)
{
	t_line	*curr;

	if ((curr = malloc(sizeof(t_line))) == NULL)
		return (NULL);
	if (*prev)
		(*prev)->next = curr;
	curr->index = position;
	curr->length = empty_len;
	curr->next = NULL;
	return (curr);
}
