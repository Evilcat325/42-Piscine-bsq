/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_bsq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:32:02 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 18:50:30 by nkirkby          ###   ########.fr       */
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
		else if (index >= LEFT_LIMIT(node) &&
				(index + range) <= (RIGHT_LIMIT(node)))
			return (SUCCESS);
		node = node->next;
	}
	return (FAILED);
}

void	update_biggest_square(t_search_state* state, int size, int row, int col)
{
	printf("recording new biggest square (%d) at col: %d\trow: %d", size, col, row);
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
										node->index, square_size))
		{
			;
		}
		col++;
	}
	if (state->current_row - row == square_size)
	{
		update_biggest_square(state, square_size, row, col);
	}
}

/*
**	Iterate over all lines
*/

void		ft_find_biggest_square(t_search_state *state)
{
	t_line		*this_line;
	t_spacenode	*node;
	int			row;

	row = 0;
	while ((this_line = &(state->lines[row])))
	{
		while ((node = (this_line->nodes)++))
		{
			if (node->length < state->biggest_square->size)
				continue ;  // There isn't enough space to grow a bigger square here.
			grow_square(state, node);
			printf("%d\t%d\n", node->index, node->length);
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
