/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:28:24 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 21:46:38 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <unistd.h>
#include <fcntl.h>

int		main(int argc, char **argv)
{
	int		i;
	int		fd;

	i = 1;
	if (argc < 2)
		ft_solve_bsq(STDIN_FILENO);
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
			ft_map_error("fail to open file");
		else
			ft_solve_bsq(fd);
		i++;
	}
}
