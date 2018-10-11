/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_bsq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:32:02 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 19:44:31 by seli             ###   ########.fr       */
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

int			line_is_empty_in_range(t_spacenode *node, int index, int range)
{
	while (node)
	{
		if (index < LEFT_LIMIT(node))
			return (FAILED);
		else if ((index + range) <= (RIGHT_LIMIT(node)))
			return (SUCCESS);
		node = node->next;
	}
	return (FAILED);
}

void	update_biggest_square(t_search_state* state, int size, int row, int col)
{
	printf("recording new biggest square (size %d) at col: %d\trow: %d\n", size, col, row);
	state->biggest_square->col = col;
	state->biggest_square->row = row;
	state->biggest_square->size = size;
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
	int row;
	int	col;

	square_size = state->biggest_square->size;
	col = node->index;
	while (col + state->biggest_square->size < RIGHT_LIMIT(node))
	{
		row = state->current_row;
		while (line_is_empty_in_range(&(state->lines[row].nodes[0]),
										node->index, square_size) && row > 0)
		{
			printf("current row: %d\n", row);
			if (state->current_row - row + 1 > square_size)
			{
				printf("current row: %d, row: %d, square_size: %d\n", state->current_row, row, square_size);
				update_biggest_square(state, state->current_row - row,
										row, col);
			}
			row--;
		}
		col++;
	}
}

/*
**	Iterate over all lines
*/

void		ft_find_biggest_square(t_search_state *state)
{
	t_spacenode	*node;
	int			row;

	row = 0;
	while (row < state->file_info->height)
	{
		if (&(state->lines[row]))
		{
			node = state->lines[row].nodes;
			while (node)
			{
				if (node->length >= state->biggest_square->size)
					grow_square(state, node);
				node = node->next;
			}
		}
		row++;
	}
}

int			ft_solve_bsq(char *filename)
{
	int				fd;
	t_parser_state	parser_state;
	t_search_state  search_state;

	ft_initialize_parser_state(&parser_state);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	if (ft_parse_bsq(fd, &parser_state) == FAILED)
		return (ft_map_error("FAILED TO PAAAARSE"));
	close(fd);
	ft_print_map(&parser_state);
	ft_print_map_list(&parser_state);
	ft_initialize_search_state(&search_state, &parser_state);
	ft_find_biggest_square(&search_state);

	// free the memory;
	return (0);
}
