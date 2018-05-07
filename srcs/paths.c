/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakwins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 20:03:14 by msakwins          #+#    #+#             */
/*   Updated: 2017/10/10 21:09:24 by msakwins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				get_next_room(t_engine *engine, int i_room)
{
	int			i;
	int			minimal;
	int			dist_min;

	i = 0;
	dist_min = -1;
	while (i < engine->rooms[i_room].nb_paths)
	{
		if (engine->rooms[engine->rooms[i_room].paths[i]].blocked == 0 &&
				engine->rooms[engine->rooms[i_room].paths[i]].dist != -1)
		{
			if (dist_min == -1 ||
				(engine->rooms[engine->rooms[i_room].paths[i]].dist < dist_min
				&& engine->rooms[i_room].dist >
				engine->rooms[engine->rooms[i_room].paths[i]].dist))
			{
				dist_min = engine->rooms[engine->rooms[i_room].paths[i]].dist;
				minimal = engine->rooms[i_room].paths[i];
			}
		}
		i++;
	}
	return (minimal);
}

int				used_room(t_engine *engine, int i_room)
{
	int			i;
	int			j;

	i = 0;
	while (i < engine->nb_paths)
	{
		j = 1;
		while (engine->paths[i][j] != 1)
		{
			if (engine->paths[i][j] == i_room)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int				*record_path(t_engine *engine)
{
	int			*path;
	int			index;
	int			i;

	if (!(path = (int *)malloc(sizeof(int) * engine->nb_rooms + 1)))
		return (NULL);
	index = 0;
	path[0] = engine->rooms[0].dist + 1;
	path[1] = 0;
	i = 2;
	while (index != 1)
	{
		path[i] = get_next_room(engine, index);
		index = path[i];
		i++;
	}
	return (path);
}

void			block_path(t_engine *engine)
{
	int			i_room;

	i_room = 2;
	engine->rooms[0].dist = -1;
	engine->rooms[1].dist = -1;
	while (i_room < engine->nb_rooms)
	{
		engine->rooms[i_room].dist = -1;
		if (used_room(engine, i_room))
			engine->rooms[i_room].blocked = 1;
		i_room++;
	}
}
