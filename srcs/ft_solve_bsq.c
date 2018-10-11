/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_bsq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:32:02 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 21:05:31 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


#define RIGHT_LIMIT(SPACENODE) (SPACENODE->index + SPACENODE->length)
#define LEFT_LIMIT(SPACENODE) (SPACENODE->index)

/*
**	Returns SUCCESS if a line contains empty spaces greater than or equal to
**	range at x-position index.
*/

void	update_biggest_square(t_search_state *state, int size, int row, int col)
{
	state->biggest_square->col = col;
	state->biggest_square->row = row;
	state->biggest_square->size = size;
}

/*
**	check if enough space is at row col with size
*/

int		ft_check_space(t_search_state *state, int size, int row, int col)
{
	t_spacenode	*node;

	if (!&state->lines[row])
		return (FAILED);
	node = state->lines[row].nodes;
	while (node)
	{
		if (node->index > col)
			return (FAILED);
		if (LEFT_LIMIT(node) <= col && col + size <= RIGHT_LIMIT(node))
			return (SUCCESS);
		node = node->next;
	}
	return (FAILED);
}

/*
**	grow the square upwards and leftwards if there is space on prior lines.
**	Returns a solution if and only if the square is bigger than the existing
**	largest square.
**	Else, returns NULL
*/

void	grow_square(t_search_state *state, const t_spacenode *node)
{
	int	square_size;
	int s_row;
	int	col;
	int	found;

	square_size = state->biggest_square->size + 1;
	col = 0;
	while (LEFT_LIMIT(node) + col + square_size <= RIGHT_LIMIT(node))
	{
		found = SUCCESS;
		s_row = 0;
		while (s_row < square_size && state->current_row - s_row >= 0 && found)
		{
			if (!ft_check_space(state, square_size,
					state->current_row - s_row, LEFT_LIMIT(node) + col))
				found = FAILED;
			s_row++;
		}
		if (found == SUCCESS && s_row == square_size)
			update_biggest_square(state, square_size++,
					state->current_row, LEFT_LIMIT(node) + col);
		else
			col++;
	}
}

/*
**	Iterate over all lines
*/

void		ft_find_biggest_square(t_search_state *state)
{
	t_spacenode	*node;

	state->current_row = 0;
	while (state->current_row < state->file_info->height)
	{
		if (&(state->lines[state->current_row]))
		{
			node = state->lines[state->current_row].nodes;
			while (node)
			{
				if (node->length >= state->biggest_square->size)
					grow_square(state, node);
				node = node->next;
			}
		}
		state->current_row += 1;
	}
}

int			ft_solve_bsq(int fd)
{
	t_parser_state	parser_state;
	t_search_state	search_state;

	ft_initialize_parser_state(&parser_state);

	if (ft_parse_bsq(fd, &parser_state) == FAILED)
		return (ft_map_error("FAILED TO PAAAARSE"));
	close(fd);
	ft_initialize_search_state(&search_state, &parser_state);
	ft_find_biggest_square(&search_state);
	ft_free_state(&parser_state);
	return (0);
}
