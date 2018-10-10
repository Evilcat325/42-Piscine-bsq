/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsq_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 20:53:18 by nkirkby           #+#    #+#             */
/*   Updated: 2018/10/10 16:14:36 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"

int		map_characters_are_not_unique(t_file_info *info)
{
	if (info->full != info->obstacle &&
		info->obstacle != info->empty &&
		info->empty != info->full)
		return (SUCCESS);
	return (ft_map_error("map characters are not unique"));
}

/*
**	If the header is valid, this function returns the starting index of the
**	first line after the header.
**	If the header is invalid, -1.
*/

int		read_bsq_header(char *str, t_file_info *info)
{
	char	line_number_descriptor[12];
	short	end_of_line;
	short	i;

	end_of_line = 0;
	while (str[end_of_line] != '\n' && end_of_line <= 15)
		if (str[end_of_line++] == '\0')
			return (ft_map_error("premature end of file in header"));
	if (end_of_line > 14)
		return (ft_map_error("header longer than expected"));
	i = end_of_line;
	info->full = str[--i];
	info->obstacle = str[--i];
	info->empty = str[--i];
	if (map_characters_are_not_unique(info) == FAILED)
		return (FAILED);
	line_number_descriptor[i] = '\0';
	while (--i >= 0)
		line_number_descriptor[i] = str[i];
	if (ft_atoi_ptr(line_number_descriptor, &(info->height)) == FAILED)
		return (FAILED);
	if ((end_of_line < 4) || info->height <= 0)
		return (ft_map_error("header shorter than expected || height <= 0"));
	return (end_of_line + 1);
}
