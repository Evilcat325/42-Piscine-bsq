/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:28:24 by seli              #+#    #+#             */
/*   Updated: 2018/10/09 23:00:54 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_main.h"

int		main(int argc, char **argv)
{
	int		i;

	i = 1;
	g_info.empty = '.';
	g_info.obstacle = 'o';
	g_info.full = 'x';
	if (argc < 2)
		return (0);
	while (i < argc)
	{
		ft_solve_bsq(argv[i]);
		i++;
	}
}
