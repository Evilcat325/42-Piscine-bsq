/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 19:06:24 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 14:10:04 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"

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
		return (FAILED);
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
		return (FAILED);
	return (len);
}
