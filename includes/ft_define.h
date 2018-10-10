/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seli <seli@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:34:51 by seli              #+#    #+#             */
/*   Updated: 2018/10/09 20:27:16 by seli             ###   ########.fr       */
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
	t_line			*next;
}					t_line;

typedef struct		s_head
{
	t_head			*prev;
	t_head			*next;
	t_line			*line;
	t_line			*search;
}					t_head;

typedef struct		s_file_information
{
	int				height;
	int				width;
	char			empty;
	char			obstacle;
	char			full;
}					t_file_information;

t_file_information	g_info;

#endif
