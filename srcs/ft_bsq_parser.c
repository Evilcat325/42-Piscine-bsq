/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsq_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 02:42:36 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 14:56:21 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <stdlib.h>
#include <unistd.h>

#define INDEX(X) (X->buf_i + X->position - X->break_position)

int			ft_parse_bsq(int fd, t_parser_state *state)
{
	char	buf[BUF_SIZE + 1];
	int		result;

	while ((result = read(fd, buf, BUF_SIZE)))
	{
		buf[result] = 0;
		if (state->file_info.height == 0
			&& (ft_parse_header(buf, state) == FAILED))
			return (FAILED);
		while (buf[state->buf_i])
			if (ft_parse_line(buf, state) == FAILED)
				return (FAILED);
	}
	return (SUCCESS);
}

int			ft_parse_header(char buf[BUF_SIZE + 1], t_parser_state *state)
{
	state->buf_i = read_bsq_header(buf, &state->file_info);
	if (state->buf_i == FAILED)
		return (FAILED);
	state->lines = malloc(sizeof(t_line) * state->file_info.height);
	if (state->lines == NULL)
		return (FAILED);
	return (SUCCESS);
}

int			ft_parse_line(char buf[BUF_SIZE + 1], t_parser_state *state)
{
	if (state->break_in_line)
		ft_parse_continue(&buf[state->buf_i], state);
	else
		ft_initialize_new_line(state);
	while (buf[INDEX(state)] != '\n')
	{
		ft_parse_next_space(&buf[INDEX(state)], state);
		if (state->break_in_line)
			break ;
	}
	if (!state->break_in_line)
	{
		if (state->file_info.width == 0)
			state->file_info.width = state->position;
		if (state->file_info.width != state->position)
			return (ft_map_error("different length in map"));
		state->line_number += 1;
		state->buf_i += 1;
	}
	state->buf_i += state->position - state->break_position;
	return (SUCCESS);
}

int			ft_parse_next_space(char *start, t_parser_state *state)
{
	int		space_len;
	int		obstcale_len;

	space_len = ft_space_len(start, state);
	if (space_len > 0)
	{
		state->curr_node =
			create_line_node(&state->curr_node, state->position, space_len);
		if (!state->lines[state->line_number].nodes)
			state->lines[state->line_number].nodes = state->curr_node;
		state->position += space_len;
	}
	else if (space_len == 0)
	{
		obstcale_len = ft_obstacle_len(start, state);
		state->position += obstcale_len;
	}
	else
		return (FAILED);
	return (SUCCESS);
}

int			ft_parse_continue(char *start, t_parser_state *state)
{
	int	space_len;

	state->break_position = state->position;
	if (state->break_in_line == BREAK_IN_EMPTY)
	{
		state->break_in_line = FALSE;
		space_len = ft_space_len(start, state);
		if (space_len >= 0)
		{
			state->curr_node->length += space_len;
			state->position += space_len;
		}
		else
			return (FAILED);
	}
	else
		state->break_in_line = FALSE;
	return (SUCCESS);
}
