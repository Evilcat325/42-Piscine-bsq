/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_bsq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:32:02 by seli              #+#    #+#             */
/*   Updated: 2018/10/09 20:11:19 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_solve_bsq.h"

void	ft_solve_bsq(char *filename)
{
	t_head	*head;

	if (ft_parse_bsq(filename, &head) == FAILED)
		return ;
}

int		ft_parse_bsq(char *filename, t_head **head)
{
	int		i;
	int		fd;
	int		position;
	int		space_len;
	int		result;
	int		break_in_line;
	char	buf[BUF_SIZE + 1];
	t_head	*curr_head;
	t_line	*curr_node;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_error_open(fd));
	break_in_line = FALSE;
	while ((result = read(fd, buf, BUF_SIZE)))
	{
		i = 0;
		while (buf[i])
		{
			position = 0;
			if (break_in_line == FALSE)
			{
				curr_head = creat_head_node(curr_head);
				if (!*head)
					*head = curr_head;
			}
			else
			{
				space_len = ft_space_len(buf[i], &break_in_line);
				curr_node->length += space_len;
				position += space_len;
				break_in_line = FALSE;
			}
			while (buf[i + position] != '\n')
			{
				space_len = ft_space_len(buf[i], &break_in_line);
				curr_node = create_line_node(curr_node, position, space_len);
				if (!curr_head->line)
					curr_head->line = curr_node;
				position += space_len == 0 ? ft_obstacle_len(buf[i]) : space_len;
			}
			i += position;
		}
	}
}
