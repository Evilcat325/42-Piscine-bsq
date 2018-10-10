/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solve_bsq.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:32:35 by seli              #+#    #+#             */
/*   Updated: 2018/10/09 23:50:12 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SOLVE_BSQ_H
# define FT_SOLVE_BSQ_H
# include <fcntl.h>
# include <unistd.h>
# include "ft_define.h"
# include "ft_data.h"
# include "ft_string.h"
# include "ft_test.h"

void	ft_solve_bsq(char *filename);
int		ft_parse_bsq(char *filename, t_head **head);

#endif
