/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakwins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 16:08:24 by msakwins          #+#    #+#             */
/*   Updated: 2017/10/10 21:09:10 by msakwins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static t_room	parse_room_chained_list(t_room_list *old_room, t_env *env)
{
	t_room		new_room;

	new_room.nb_paths = 0;
	new_room.name = ft_strdup(old_room->name);
	ft_strdel(&old_room->name);
	new_room.start = old_room->start;
	new_room.end = old_room->end;
	new_room.dist = -1;
	new_room.blocked = 0;
	if (!(new_room.paths = (int *)malloc(sizeof(int) * env->nb_room - 1)))
		return_error(1, "malloc failed");
	return (new_room);
}

void			parse_rooms_to_tab(t_env *env)
{
	int				i;
	int				index;
	t_room_list		*tmp;

	env->pipe_found = 1;
	if (!(env->rooms = (t_room *)malloc(sizeof(t_room) * env->nb_room)))
		return ;
	i = 0;
	tmp = env->room;
	while (tmp)
	{
		if (tmp->start)
			index = 0;
		else if (tmp->end)
			index = 1;
		else
		{
			index = i + 2;
			i++;
		}
		env->rooms[index] = parse_room_chained_list(tmp, env);
		tmp = tmp->next;
	}
}
