/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 20:31:37 by seli              #+#    #+#             */
/*   Updated: 2018/10/09 20:38:29 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

#define IS_DIGIT(X) (X >= '0' && X <= '9')
#define IS_SIGN(X) (X == '+' || X == '-')

/*
** The real atoi:
** - parses + and - signs
** - ignores leading zeros
** - starts parsing if it encounters a + sign, - sign,
** - stops parsing if it encounters a non-digit
** - overflows if the number is larger than an int
*/

int	ft_atoi(char *str)
{
	long	output;
	int		sign;

	output = 0;
	sign = 1;
	while (*str == ' ')
		str++;
	if (!(IS_DIGIT(*str) || IS_SIGN(*str)))
		return (0);
	if (IS_SIGN(*str))
		sign = *str++ == '-' ? -1 : 1;
	if (!IS_DIGIT(*str))
		return (0);
	while (*str && IS_DIGIT(*str))
	{
		output *= 10;
		output += (int)(*str++ - '0');
	}
	output *= sign;
	return (int)(output);
}
