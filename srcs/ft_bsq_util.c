/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsq_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 20:53:18 by nkirkby           #+#    #+#             */
/*   Updated: 2018/10/09 22:30:25 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_define.h"
#include "ft_bsq_util.h"
#include "ft_stdio.h"

/*
**	Returns 0 if header is valid.  -1 otherwise.
*/

int	read_bsq_header(char *str, t_file_info *info)
{
	char	line_number_descriptor[11];
	short	end_of_line;
	char	err;

	end_of_line = 0;
	while (str[end_of_line] && str[end_of_line] != '\n')
		end_of_line++;
	if (end_of_line < 4)
		return (-1);
	info->full = str[--end_of_line];
	info->obstacle = str[--end_of_line];
	info->empty = str[--end_of_line];
	line_number_descriptor[--end_of_line] = '\0';
	while (end_of_line >= 0)
	{
		line_number_descriptor[end_of_line] = str[end_of_line];
		end_of_line--;
	}
	err = ft_atoi_ptr(line_number_descriptor, &(info->height));
	if (err)
		return (-1);
	return (0);
}
