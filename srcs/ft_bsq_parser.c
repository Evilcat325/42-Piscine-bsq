/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsq_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 02:42:36 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 23:05:52 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <stdlib.h>
#include <unistd.h>

#define INDEX(X) (X->buf_i + X->position - X->break_position)

/*
**	ft_parse_bsq takes in filedescriptor and state object
**	Buffer Size is defined in header and the current logic is input agnositc
*/

int			ft_parse_bsq(int fd, t_parser_state *state)
{
	char	buf[BUF_SIZE + 1];
	int		result;

	while ((result = read(fd, buf, BUF_SIZE)))
	{
		buf[result] = 0;
		state->buf_i = 0;
		if (state->file_info.height == 0)
			if (ft_parse_header(buf, state) == FAILED)
				return (FAILED);
		if (buf[state->buf_i] == '\0')
			return (ft_map_error("no map in file"));
		while (buf[state->buf_i])
			if (ft_parse_line(buf, state) == FAILED)
				return (FAILED);
		if (buf[state->buf_i] == '\n' && buf[state->buf_i + 1] == '\0')
			break ;
	}
	if (state->line_number != state->file_info.height)
		return (ft_map_error("different actual map height vs header height"));
	return (SUCCESS);
}

/*
**	ft_parse_header is searching for the header for the map
**	return Error when the header is invalid
**	function also setting the buf_i for the parser to read the map
**	it also allocate memory for the line node as a strcut array
*/

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

/*
**	ft_parse_line will try to parse the current line as linked list
**	as the buffer might break in line, it depends on the outter buffer read
**	loop for further inpu as state->break_in_line and state->break_position
**	will keep the previous buffer info
*/

int			ft_parse_line(char buf[BUF_SIZE + 1], t_parser_state *state)
{
	if (state->break_in_line)
	{
		if (ft_parse_continue(&buf[state->buf_i], state) == FAILED)
			return (FAILED);
	}
	else
		ft_initialize_new_line(state);
	while (buf[INDEX(state)] != '\n')
	{
		if (ft_parse_next_space(&buf[INDEX(state)], state) == FAILED)
			return (FAILED);
		if (state->break_in_line)
			break ;
	}
	if (!state->break_in_line)
	{
		if (state->position == 0)
			return (ft_map_error("empty line"));
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

/*
**	ft_parse_next_space is compressing the next available space as a linked
**	list node. If it encouter invalid char, it would signal FAILED map error
**	it would also connect the linked list space node to the line node if exist
*/

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
		if (obstcale_len == FAILED)
			return (FAILED);
		state->position += obstcale_len;
	}
	else
		return (FAILED);
	return (SUCCESS);
}

/*
**	ft_parse_continue will be call when buffer is breaking in line
**	It perserves the state of position and break position to keep process
**	the new buffer while maintain the current line state.
*/

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
