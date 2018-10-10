/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 19:06:24 by seli              #+#    #+#             */
/*   Updated: 2018/10/09 20:09:15 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int		ft_space_len(char *str, int	*break_in_line)
{
	int	len;

	len = 0;
	while (*str && *str != '\n' && *str != OBSTACLE)
	{
		str++;
		len++;
	}
	if (!*str)
		*break_in_line = TRUE;
	return (len);
}
