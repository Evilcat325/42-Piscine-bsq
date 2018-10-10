/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:34:51 by seli              #+#    #+#             */
/*   Updated: 2018/10/09 21:58:17 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFINE_H
# define FT_DEFINE_H

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILED 0
# define BUF_SIZE 4096

typedef struct		s_line
{
	int				index;
	int				length;
	struct s_line	*next;
}					t_line;

typedef struct		s_head
{
	struct s_head	*prev;
	struct s_head	*next;
	struct s_head	*line;
	struct s_head	*search;
}					t_head;

typedef struct		s_file_info
{
	int				height;
	int				width;
	char			empty;
	char			obstacle;
	char			full;
}					t_file_info;

t_file_info			g_info = {
	.height = 0,
	.width = 0,
	.empty = '.',
	.obstacle = 'o',
	.full = 'x',
};

#endif
