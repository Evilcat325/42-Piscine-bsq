/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 18:33:34 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 17:21:24 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <stdlib.h>

void		ft_initialize_parser_state(t_parser_state *state)
{
	state->buf_i = 0;
	state->position = 0;
	state->break_position = 0;
	state->break_in_line = FALSE;
	state->line_number = 0;
	state->curr_node = NULL;
	state->lines = NULL;
	state->file_info.empty = 0;
	state->file_info.full = 0;
	state->file_info.obstacle = 0;
	state->file_info.height = 0;
	state->file_info.width = 0;
}

void		ft_initialize_new_line(t_parser_state *state)
{
	state->position = 0;
	state->break_position = 0;
	state->curr_node = 0;
	state->lines[state->line_number].nodes = NULL;
	state->lines[state->line_number].search = NULL;
}

void		ft_initialize_search_state(t_search_state *search_state,
							const t_parser_state *parser_state)
{
	search_state->lines = parser_state->lines;
	search_state->file_info = &(parser_state->file_info);
	search_state->current_row = 0;
	search_state->biggest_square->col = 0;
	search_state->biggest_square->row = 0;
	search_state->biggest_square->size = 0;
}

t_spacenode	*create_line_node(t_spacenode **prev, int position,
								int empty_len)
{
	t_spacenode	*curr;

	if ((curr = malloc(sizeof(t_spacenode))) == NULL)
		return (NULL);
	if (*prev)
		(*prev)->next = curr;
	curr->index = position;
	curr->length = empty_len;
	curr->next = NULL;
	return (curr);
}

// t_line			*previous_line(t_parser_state *state, int current_row)
// {
// 	if (current_row < 1 || current_row > state->file_info->height)
// 		return (NULL);
// 	return (&(state->lines[current_row - 1]));
// }

t_square		*new_square(int row, int col)
{
	t_square *square;

	if ((square = malloc(sizeof(t_square))))
		return (NULL);
	square->row = row;
	square->col = col;
	square->size = 0;
	return (square);
}
