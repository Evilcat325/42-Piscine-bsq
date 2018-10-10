/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 18:33:47 by seli              #+#    #+#             */
/*   Updated: 2018/10/09 19:30:19 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DATA_H
# define FT_DATA_H
# include "ft_define.h"

t_head		*create_head_node(t_head *prev);
t_line		*create_line_node(t_line *prev, int position, int dot_len);

#endif
