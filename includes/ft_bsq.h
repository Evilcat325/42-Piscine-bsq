/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsq.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:34:51 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 00:34:12 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BSQ_H
# define FT_BSQ_H

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

t_head				*create_head_node(t_head **prev);
t_line				*create_line_node(t_line **prev, int position,
										int empty_len);

int					read_bsq_header(char *str, t_file_info *info);
int					ft_map_error(void);
void				ft_solve_bsq(char *filename);
int					ft_parse_bsq(char *filename, t_head **head);
int					ft_atoi_ptr(char *str, int *out);
int					ft_space_len(char *str, int	*break_in_line);
int					ft_obstacle_len(char *str, int *break_in_line);
void				ft_print_map_list(t_head *head);

#endif
