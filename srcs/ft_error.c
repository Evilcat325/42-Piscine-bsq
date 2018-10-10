/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 17:02:42 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 02:48:59 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <unistd.h>

#define UNUSED(x) (void)(x)

int		ft_map_error(char *msg)
{
	UNUSED(msg);
	write(1, "map error\n", 10);
	return (-1);
}
