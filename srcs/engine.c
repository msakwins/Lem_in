/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakwins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 20:54:31 by msakwins          #+#    #+#             */
/*   Updated: 2017/10/10 21:45:55 by msakwins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			dfs(t_engine *engine, int index, int dist)
{
	int			i;

	if (engine->rooms[index].blocked == 1)
		return ;
	if (engine->rooms[index].dist != -1 && dist > engine->rooms[index].dist)
		return ;
	engine->rooms[index].dist = dist;
	if (index == 0)
		return ;
	i = 0;
	while (i < engine->rooms[index].nb_paths)
	{
		dfs(engine, engine->rooms[index].paths[i], dist + 1);
		i++;
	}
}

static void		debug(t_engine *engine)
{
	int			j;
	int			i;

	i = 0;
	while (i < engine->nb_paths)
	{
		j = 1;
		ft_printf("\e[92m%s%d %s%d %s", "Path ", i, "dist = ",
				engine->paths[i][0], "and is : ");
		while (j < engine->paths[i][0])
		{
			ft_putstr(engine->rooms[engine->paths[i][j]].name);
			ft_putchar('-');
			j++;
		}
		ft_putstr(engine->rooms[engine->paths[i][j]].name);
		ft_putendl("\n");
		i++;
	}
}

void			start_engine(t_engine *engine)
{
	int			i;
	int			possib_path;

	possib_path = engine->rooms[0].nb_paths;
	possib_path = engine->rooms[1].nb_paths < possib_path ?
		engine->rooms[1].nb_paths : possib_path;
	if (!(engine->paths = malloc(sizeof(int *) * possib_path)))
		return ;
	i = 0;
	while (i < possib_path)
	{
		dfs(engine, 1, 0);
		if (engine->rooms[0].dist != -1)
		{
			engine->nb_paths += 1;
			engine->paths[i] = record_path(engine);
			block_path(engine);
		}
		i++;
	}
	if (engine->nb_paths == 0)
		return_error(1, "No path found");
	if (engine->debug)
		debug(engine);
	init_cats(engine);
}
