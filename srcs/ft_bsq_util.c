/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsq_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 20:53:18 by nkirkby           #+#    #+#             */
/*   Updated: 2018/10/10 03:11:24 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"

/*
**	Returns the index of the end of the header if valid.  -1 otherwise.
*/

int		read_bsq_header(char *str, t_file_info *info)
{
	char	line_number_descriptor[11];
	short	end_of_line;
	short	i;
	char	err;

	end_of_line = 0;
	while (str[end_of_line] && str[end_of_line] != '\n')
		end_of_line++;
	if (end_of_line < 4)
		return (-1);
	i = end_of_line;
	info->full = str[--i];
	info->obstacle = str[--i];
	info->empty = str[--i];
	line_number_descriptor[--i] = '\0';
	while (i >= 0)
	{
		line_number_descriptor[i] = str[i];
		i--;
	}
	err = ft_atoi_ptr(line_number_descriptor, &(info->height));
	if (err)
		return (-1);
	return (end_of_line);
}
