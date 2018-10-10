/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:34:51 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 00:19:07 by seli             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFINE_H
# define FT_DEFINE_H

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILED 0
# define BUF_SIZE 1
# define BREAK_IN_EMPTY 1
# define BREAK_IN_OBSTACLE 2

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
	struct s_line	*line;
	struct s_line	*search;
}					t_head;

typedef struct		s_file_info
{
	int				height;
	int				width;
	char			empty;
	char			obstacle;
	char			full;
}					t_file_info;

t_file_info			g_info;

#endif
