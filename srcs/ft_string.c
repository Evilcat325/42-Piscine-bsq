/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 19:06:24 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 22:32:00 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <stdlib.h>

int		ft_space_len(char *str, t_parser_state *state)
{
	int	len;

	len = 0;
	while (*str && *str != '\n' && *str == state->file_info.empty)
	{
		str++;
		len++;
	}
	if (!*str)
		state->break_in_line = BREAK_IN_EMPTY;
	else if (*str != state->file_info.empty
				&& *str != state->file_info.obstacle && *str != '\n')
		return (ft_map_error("invalid char after space"));
	return (len);
}

int		ft_obstacle_len(char *str, t_parser_state *state)
{
	int	len;

	len = 0;
	while (*str && *str != '\n' && *str == state->file_info.obstacle)
	{
		str++;
		len++;
	}
	if (!*str)
		state->break_in_line = BREAK_IN_OBSTACLE;
	else if (*str != state->file_info.empty
				&& *str != state->file_info.obstacle && *str != '\n')
		return (ft_map_error("invalid char after obstacle"));
	return (len);
}

void	ft_initialize_string(t_string_state *strings, t_parser_state *state,
							t_square *biggest_square)
{
	int		i;

	i = 0;
	strings->empty = malloc(sizeof(char) * (state->file_info.width + 1));
	strings->obstacle = malloc(sizeof(char) * (state->file_info.width + 1));
	strings->square = malloc(sizeof(char) * (biggest_square->size + 1));
	while (i <= state->file_info.width)
	{
		strings->empty[i] = state->file_info.empty;
		strings->obstacle[i] = state->file_info.obstacle;
		if (i < biggest_square->size)
			strings->square[i] = state->file_info.full;
		i++;
	}
	strings->empty[i] = 0;
	strings->obstacle[i] = 0;
	strings->square[biggest_square->size] = 0;
}
