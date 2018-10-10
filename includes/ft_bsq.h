/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bsq.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkirkby <nkirkby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 16:34:51 by seli              #+#    #+#             */
/*   Updated: 2018/10/10 14:52:40 by nkirkby          ###   ########.fr       */
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

typedef struct			s_spacenode
{
	int					index;
	int					length;
	struct s_spacenode	*next;
}						t_spacenode;

typedef struct			s_line
{
	struct s_spacenode	*nodes;
	struct s_spacenode	*search;
}						t_line;

typedef struct			s_file_info
{
	int					height;
	int					width;
	char				empty;
	char				obstacle;
	char				full;
}						t_file_info;

typedef struct			s_square
{
	int					row;
	int					col;
	int					size;
}						t_square;

/*
**	buf_i : buffer index
*/

typedef struct			s_parser_state
{
	int					buf_i;
	int					position;
	int					break_position;
	int					break_in_line;
	int					line_number;
	t_line				*lines;
	t_spacenode			*curr_node;
	t_file_info			file_info;
	t_square			biggest_square;
}						t_parser_state;

void					ft_initialize_parser_state(t_parser_state *state);
void					ft_initialize_new_line(t_parser_state *state);
t_spacenode				*create_line_node(t_spacenode **prev, int position,
											int empty_len);

int						ft_parse_bsq(int fd, t_parser_state *state);
int						ft_parse_header(char buf[BUF_SIZE + 1],
										t_parser_state *state);
void					ft_parse_line(char buf[BUF_SIZE + 1],
										t_parser_state *state);
int						ft_parse_next_space(char *start,
										t_parser_state *state);
int						ft_parse_continue(char *start,
										t_parser_state *state);

int						read_bsq_header(char *str, t_file_info *info);
int						ft_map_error(char *msg);
int						ft_solve_bsq(char *filename);
int						ft_parse_bsq(int fd, t_parser_state *state);
int						ft_atoi_ptr(char *str, int *out);
int						ft_space_len(char *str, t_parser_state *state);
int						ft_obstacle_len(char *str, t_parser_state *state);

void					ft_print_map_list(t_parser_state *state);
void					ft_print_map(t_parser_state *state);

#endif
