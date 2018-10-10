/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 18:33:47 by seli              #+#    #+#             */
/*   Updated: 2018/10/09 22:29:24 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DATA_H
# define FT_DATA_H
# include <stdlib.h>
# include "ft_define.h"

t_head		*create_head_node(t_head *prev);
t_line		*create_line_node(t_line *prev, int position, int empty_len);

#endif
