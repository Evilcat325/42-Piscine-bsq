/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:28:24 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 00:27:45 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"

int		main(int argc, char **argv)
{
	int		i;

	i = 1;
	if (argc < 2 || !read_bsq_header(argv[1], &g_info))
		return (ft_map_error());
	while (i < argc)
	{
		ft_solve_bsq(argv[i]);
		i++;
	}
}
