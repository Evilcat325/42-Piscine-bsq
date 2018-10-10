/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 19:06:50 by seli              #+#    #+#             */
/*   Updated: 2018/10/09 22:08:07 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H
# include "ft_define.h"

extern t_file_info	g_info;

int					ft_space_len(char *str, int	*break_in_line);
int					ft_obstacle_len(char *str, int *break_in_line);

#endif
