/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsq_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 20:53:18 by nkirkby           #+#    #+#             */
/*   Updated: 2018/10/09 21:30:48 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_define.h"
#include "ft_bsq_util.h"

void	read_bsq_header(char *str, t_file_info *info)
{
	char *end_of_line;


	info->height = ft_atoi(*str);
}
