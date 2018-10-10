/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_bsq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:32:02 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 13:40:47 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void	ft_find_biggest_square(char);

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
