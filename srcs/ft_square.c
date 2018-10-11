/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 21:58:28 by nkirkby           #+#    #+#             */
/*   Updated: 2018/10/10 21:59:22 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <stdlib.h>

t_square	*new_square(int row, int col)
{
	t_square *square;

	if ((square = malloc(sizeof(t_square))))
		return (NULL);
	square->row = row;
	square->col = col;
	square->size = 0;
	return (square);
}
