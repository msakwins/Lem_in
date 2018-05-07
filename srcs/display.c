/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakwins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/01 17:54:43 by msakwins          #+#    #+#             */
/*   Updated: 2017/10/10 21:04:39 by msakwins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		bufferize(t_env *env, char *line)
{
	env->buffer = ft_strjoin_mod_nl(env->buffer, line);
	if (env->buffer == NULL)
		return_error(1, "Failed to allocate buffer");
}

void		printf_buffer(t_env *env)
{
	if (env->debug)
		ft_printf("\e[35m");
	ft_putendl(env->buffer);
}

void		display(t_engine engine)
{
	int		i;
	int		j;

	i = 0;
	while (i < engine.nb_rooms)
	{
		ft_printf("\e[93m%s%s", "The room ", engine.rooms[i].name);
		if (engine.rooms[i].nb_paths > 1)
			ft_putendl(" have paths to the rooms : ");
		else
			ft_putendl(" have a path to the room : ");
		j = 0;
		while (j < engine.rooms[i].nb_paths)
		{
			ft_putstr(" * ");
			ft_putendl(engine.rooms[engine.rooms[i].paths[j]].name);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
