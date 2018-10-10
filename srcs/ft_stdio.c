/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdio.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 20:31:37 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 00:33:04 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bsq.h"
#include <stdio.h>

#define IS_DIGIT(X) (X >= '0' && X <= '9')
#define IS_SIGN(X) (X == '+' || X == '-')

/*
**	This version of atoi mutates a pointed-to integer
**	Returns 0 if succesful, other if the argument is invalid.
*/

int	ft_atoi_ptr(char *str, int *out)
{
	int	output;
	int	sign;

	output = 0;
	sign = 1;
	while (*str == ' ')
		str++;
	if (!(IS_DIGIT(*str) || IS_SIGN(*str)))
		return (-1);
	if (IS_SIGN(*str))
		sign = *str++ == '-' ? -1 : 1;
	if (!IS_DIGIT(*str))
		return (-1);
	while (*str && IS_DIGIT(*str))
	{
		output *= 10;
		output += (int)(*str++ - '0');
	}
	output *= sign;
	*out = (output);
	return (0);
}

void	ft_print_map_list(t_head *head)
{
	t_line		*node;

	node = NULL;
	while (head)
	{
		node = head->line;
		while (node)
		{
			printf("index: %d, length: %d |", node->index, node->length);
			node = node->next;
		}
		printf("\n");
		head = head->next;
	}
}
