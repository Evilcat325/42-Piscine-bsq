/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsq.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:34:51 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 10:28:28 by nkirkby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BSQ_H
# define FT_BSQ_H

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

typedef struct		s_parser_state
{
	int				buf_i;
	int				position;
	int				break_position;
	int				break_in_line;
	int				line_number;
	t_head			*head_list;
	t_line			*curr_node;
}					t_parser_state;

t_file_info			g_info;

void				ft_initialize_parser_state(t_parser_state *state);
void				ft_initialize_new_line(t_parser_state *state);
t_line				*create_line_node(t_line **prev, int position,
										int empty_len);

int					ft_parse_bsq(int fd, t_parser_state *state);
int					ft_parse_header(char buf[BUF_SIZE + 1],
									t_parser_state *state);
void				ft_parse_line(char buf[BUF_SIZE + 1],
									t_parser_state *state);
int					ft_parse_next_space(char *start,
									t_parser_state *state);
int					ft_parse_continue(char *start,
									t_parser_state *state);

int					read_bsq_header(char *str, t_file_info *info);
int					ft_map_error(char *msg);
int					ft_solve_bsq(char *filename);
int					ft_parse_bsq(int fd, t_parser_state *state);
int					ft_atoi_ptr(char *str, int *out);
int					ft_space_len(char *str, int	*break_in_line);
int					ft_obstacle_len(char *str, int *break_in_line);

void				ft_print_map_list(t_parser_state *state);
void				ft_print_map(t_parser_state *state);

#endif
