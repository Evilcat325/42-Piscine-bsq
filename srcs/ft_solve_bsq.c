/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_bsq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:32:02 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 14:15:28 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


void	is_largest_square()

/*
**	grow the square if there is space on prior lines.  Returns a solution if
**	and only if the square is bigger than the existing largest square.
*/

void	check_prior_lines(t_head *this_line, t_line *space)
{

}

/*
**	Iterate over all lines
*/

void	ft_find_biggest_square(t_parser_state *state)
{
	t_head	*this_line;
	t_head	*prior_line;
	t_line	*space;

	head = state->head_list;
	while (head)
	{
		space = head->line;
		while (space)
		{
			// iterate up through previous head to see how big the square is.

			if space->
			space = space->next;
		}
		head = head->next;
	}
}

int		ft_solve_bsq(char *filename)
{
	int				fd;
	t_parser_state	state;

	ft_initialize_parser_state(&state);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (FALSE);
	if (ft_parse_bsq(fd, &state) == FAILED)
		return (ft_map_error("FAILED TO PAAAARSE"));
	close(fd);
	ft_print_map_list(&state);
	ft_print_map(&state);
	// free the memory;
	return (0);
}
