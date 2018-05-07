/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakwins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 18:40:57 by msakwins          #+#    #+#             */
/*   Updated: 2017/10/10 22:38:05 by msakwins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void		parse_pipe_into_rooms(t_env *env, int index_a, int index_b)
{
	int			new_path_index;

	same_pipe(env->rooms[index_a], env->rooms[index_b], index_a, index_b);
	new_path_index = env->rooms[index_a].nb_paths;
	env->rooms[index_a].paths[new_path_index] = index_b;
	new_path_index = env->rooms[index_b].nb_paths;
	env->rooms[index_b].paths[new_path_index] = index_a;
	env->rooms[index_a].nb_paths += 1;
	env->rooms[index_b].nb_paths += 1;
}

int				parse_pipe(t_env *env, char *line)
{
	char		**pipe;
	int			i;
	int			index_a;
	int			index_b;

	index_a = -1;
	index_b = -1;
	i = 0;
	env->pipe_found = 1;
	pipe = ft_strsplit(line, '-');
	if (ft_strequ(pipe[0], pipe[1]))
		return_error(1, "Pipe is connected to itself");
	while (i < env->nb_room)
	{
		if (ft_strequ(env->rooms[i].name, pipe[0]))
			index_a = i;
		if (ft_strequ(env->rooms[i].name, pipe[1]))
			index_b = i;
		i++;
	}
	if (index_a == -1 || index_b == -1)
		return_error(0, "Path not found, room not connected or bad pipe");
	free_tab(pipe);
	parse_pipe_into_rooms(env, index_a, index_b);
	return (0);
}

int				parse_room(t_env *env, char **tab)
{
	t_room_list	*new_room;

	if (check_room_format(tab))
	{
		if (!(new_room = malloc(sizeof(t_room_list))))
			return (0);
		new_room->start = env->start_found == 1 ? 1 : 0;
		env->start_found = new_room->start == 1 ? 2 : env->start_found;
		new_room->end = env->end_found == 1 ? 1 : 0;
		env->end_found = new_room->end == 1 ? 2 : env->end_found;
		new_room->name = ft_strdup(tab[0]);
		new_room->x = ft_atoi(tab[1]);
		new_room->y = ft_atoi(tab[2]);
		check_room_name(env, new_room->name, new_room->x, new_room->y);
		new_room->next = env->room;
		env->room = new_room;
	}
	else
		return_error(1, "Wrong room format");
	return (0);
}

int				parse_lines(t_env *env, char *line)
{
	char		**split;

	split = ft_strsplit(line, ' ');
	if (line[0] == '#' && line[1] == '#')
		parse_start_end(env, line);
	else if (line[0] == '#' && line[1] != '#')
		parse_comment(line);
	else if (is_room(split, line))
	{
		if (env->pipe_found == 1)
			return_error(1, "No room allowed after a pipe");
		parse_room(env, split);
		env->nb_room++;
	}
	else if (ft_strchr(line, '-'))
	{
		if (is_pipe(env, split))
			parse_pipe(env, line);
	}
	else
		return_error(1, "Unknown line");
	free_tab(split);
	return (0);
}

int				parse_lem(t_env *env)
{
	char		*line;
	int			ret;

	ret = 0;
	if ((ret = get_next_line(env->fd, &line)) != 1)
		return_error(2, "You should not");
	parse_cats(env, line);
	bufferize(env, line);
	free(line);
	while (ret == get_next_line(env->fd, &line) > 0)
	{
		parse_lines(env, line);
		bufferize(env, line);
		free(line);
	}
	return (0);
}
