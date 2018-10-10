/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsq_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 02:42:36 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 03:46:51 by seli             ###   ########.fr       */
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
		if (g_info.height == 0 && (ft_parse_header(buf, state) == FAILED))
			return (FAILED);
		while (buf[state->buf_i])
			ft_parse_line(buf, state);
	}
	return (SUCCESS);
}

int			ft_parse_header(char buf[BUF_SIZE + 1], t_parser_state *state)
{
	state->buf_i = read_bsq_header(buf, &g_info);
	if (state->buf_i == FAILED)
		return (FAILED);
	state->head_list = malloc(sizeof(t_head) * g_info.height);
	if (state->head_list == NULL)
		return (FAILED);
	return (SUCCESS);
}

void		ft_parse_line(char buf[BUF_SIZE + 1], t_parser_state *state)
{
	if (state->break_in_line == FALSE)
		ft_initialize_new_line(state);
	else
		ft_parse_continue(&buf[state->buf_i], state);
	while (buf[INDEX(state)] != '\n' && !state->break_in_line)
		ft_parse_next_space(&buf[INDEX(state)], state);
	state->line_number += state->break_in_line ? 0 : 1;
	state->buf_i += state->position - state->break_position;
	state->buf_i += (state->break_in_line ? 0 : 1);
}

int			ft_parse_next_space(char *start, t_parser_state *state)
{
	int		space_len;
	int		obstcale_len;

	space_len = ft_space_len(start, &state->break_in_line);
	if (space_len != 0)
	{
		state->curr_node =
			create_line_node(&state->curr_node, state->position, space_len);
		if (!state->head_list[state->line_number].line)
			state->head_list[state->line_number].line = state->curr_node;
		state->position += space_len;
	}
	else
	{
		obstcale_len = ft_obstacle_len(start, &state->break_in_line);
		state->position += obstcale_len;
	}
	return (SUCCESS);
}

int			ft_parse_continue(char *start, t_parser_state *state)
{
	int	space_len;

	state->break_position = state->position;
	if (state->break_in_line == BREAK_IN_EMPTY)
	{
		state->break_in_line = FALSE;
		space_len = ft_space_len(start, &state->break_in_line);
		state->curr_node->length += space_len;
		state->position += space_len;
	}
	else
		state->break_in_line = FALSE;
	return (SUCCESS);
}
