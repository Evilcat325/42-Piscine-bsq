/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_bsq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:32:02 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 20:41:04 by seli             ###   ########.fr       */
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
	printf("recording new biggest square (size %d) at col: %d\trow: %d\n",
			size, col, row);
	state->biggest_square->col = col;
	state->biggest_square->row = row;
	state->biggest_square->size = size;
}

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
	int backward_row;
	int	col;
	int	found;

	square_size = state->biggest_square->size + 1;
	col = 0;
	while (LEFT_LIMIT(node) + col + square_size <= RIGHT_LIMIT(node))
	{
		found = SUCCESS;
		backward_row = 0;
 		while (backward_row < square_size && state->current_row - backward_row >= 0)
		{
			if (!ft_check_space(state, square_size,
					state->current_row - backward_row, LEFT_LIMIT(node) + col))
			{
				found = FAILED;
				break ;
			}
			backward_row++;
		}
		if (found == SUCCESS && backward_row == square_size)
		{
			update_biggest_square(state, square_size,
					state->current_row, LEFT_LIMIT(node) + col);
			square_size++;
		}
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

int			ft_solve_bsq(char *filename)
{
	int				fd;
	t_parser_state	parser_state;
	t_search_state	search_state;

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
	return (0);
}
