/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:34:51 by seli              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/10/09 22:10:14 by seli             ###   ########.fr       */
=======
/*   Updated: 2018/10/09 21:58:17 by nkirkby          ###   ########.fr       */
>>>>>>> 0a3e35755b3d1b645839ba9b234db8bfa842ed15
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DEFINE_H
# define FT_DEFINE_H

# define TRUE 1
# define FALSE 0
# define SUCCESS 1
# define FAILED 0
# define BUF_SIZE 4096
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
<<<<<<< HEAD
	struct s_line	*line;
	struct s_line	*search;
=======
	struct s_head	*line;
	struct s_head	*search;
>>>>>>> 0a3e35755b3d1b645839ba9b234db8bfa842ed15
}					t_head;

typedef struct		s_file_info
{
	int				height;
	int				width;
	char			empty;
	char			obstacle;
	char			full;
}					t_file_info;

<<<<<<< HEAD
t_file_info			g_info;
=======
t_file_info			g_info = {
	.height = 0,
	.width = 0,
	.empty = '.',
	.obstacle = 'o',
	.full = 'x',
};
>>>>>>> 0a3e35755b3d1b645839ba9b234db8bfa842ed15

#endif
