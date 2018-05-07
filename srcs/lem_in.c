/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakwins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 15:17:33 by msakwins          #+#    #+#             */
/*   Updated: 2017/10/10 22:50:13 by msakwins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_engine	get_engine(t_env *env)
{
	t_engine		engine;
	t_room_list		*tmp;
	t_room_list		*fst;

	engine.nb_cats = env->cats;
	engine.nb_rooms = env->nb_room;
	engine.rooms = env->rooms;
	engine.debug = env->debug;
	engine.nb_paths = 0;
	fst = env->room;
	if (!env->start_found || !env->end_found)
		return_error(1, "No start or end found");
	if (!env->pipe_found)
		return_error(0, "No pipe found");
	while (fst)
	{
		tmp = fst->next;
		ft_memdel((void **)&fst);
		fst = tmp;
	}
	env->room = NULL;
	return (engine);
}

int				main(void)
{
	t_env		env;
	t_engine	engine;

	init(&env);
	parse_lem(&env);
	printf_buffer(&env);
	engine = get_engine(&env);
	if (engine.debug)
		display(engine);
	start_engine(&engine);
	return (0);
}
