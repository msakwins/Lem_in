/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakwins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 20:07:26 by msakwins          #+#    #+#             */
/*   Updated: 2017/10/10 20:06:46 by msakwins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# define LEM_IN_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define RED "\x1B[31m"
# define CYAN "\x1b[36m"
# define NOP "\033[0m"

typedef struct			s_room_list
{
	int					start;
	int					end;
	int					x;
	int					y;
	char				*name;
	struct s_room_list	*next;
}						t_room_list;

typedef struct			s_room
{
	int					*paths;
	int					start;
	int					end;
	int					nb_paths;
	int					blocked;
	int					next_room;
	int					dist;
	char				*name;
}						t_room;

typedef struct			s_cat
{
	int					path_chosen;
	int					cur_pos;
}						t_cat;

typedef struct			s_engine
{
	int					nb_cats;
	int					nb_paths;
	int					**paths;
	int					nb_rooms;
	int					debug;
	t_room				*rooms;
	t_cat				*cats;
}						t_engine;

typedef struct			s_env
{
	int					fd;
	int					cats;
	int					nb_room;
	int					start_found;
	int					end_found;
	int					nb_line;
	int					pipe_found;
	char				*buffer;
	int					debug;
	t_room_list			*room;
	t_room				*rooms;
}						t_env;

int						parse_lem(t_env *env);
int						parse_cats(t_env *env, char *line);
int						parse_start_end(t_env *env, char *line);
int						parse_lines(t_env *env, char *line);
int						parse_pipe(t_env *env, char *line);
int						parse_comment(char *line);
int						parse_room(t_env *env, char **tab);
int						is_room(char **tab, char *line);
int						is_pipe(t_env *env, char **tab);
void					same_pipe(t_room room_a, t_room room_b,
		int index_a, int index_b);
int						check_room_format(char **tab);
int						check_room_name(t_env *env, char *name, int x, int y);
void					parse_rooms_to_tab(t_env *env);
void					start_engine(t_engine *engine);
void					dfs(t_engine *engine, int index, int dist);
int						used_room(t_engine *engine, int i_room);
int						*record_path(t_engine *engine);
void					block_path(t_engine *engine);
int						get_next_room(t_engine *engine, int i_room);
void					init_cats(t_engine *engine);
int						continue_moving(t_engine *engine);
int						get_index_lower(int nb_paths, int cat_nb);
void					display_result(t_engine *engine);
int						count_blanks(char *str);
void					bufferize(t_env *env, char *line);
void					display(t_engine engine);
void					printf_buffer(t_env *env);
void					init(t_env *env);
void					check_errors(t_env *env);
void					return_error(int i, char *error);

#endif
