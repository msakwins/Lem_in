/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakwins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 22:10:28 by msakwins          #+#    #+#             */
/*   Updated: 2017/10/10 21:04:29 by msakwins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			count_blanks(char *str)
{
	int			blanks;

	blanks = 0;
	while (*str != '\0')
	{
		if (*str == ' ' || *str == '\t')
			blanks++;
		str++;
	}
	return (blanks);
}

void		same_pipe(t_room room_a, t_room room_b, int index_a, int index_b)
{
	int			i;
	int			j;

	i = 0;
	while (i < room_a.nb_paths)
	{
		if (room_a.paths[i] == index_b)
			return_error(0, "Pipe already registered");
		i++;
	}
	j = 0;
	while (j < room_b.nb_paths)
	{
		if (room_b.paths[j] == index_a)
			return_error(0, "Pipe already registered");
		j++;
	}
}

int			check_room_name(t_env *env, char *name, int x, int y)
{
	t_room_list	*tmp;

	tmp = env->room;
	while (tmp)
	{
		if (ft_strequ(tmp->name, name))
			return_error(1, "Room name already used");
		if (tmp->x == x && tmp->y == y)
			return_error(1, "Room location already taken");
		tmp = tmp->next;
	}
	return (0);
}

int			check_room_format(char **tab)
{
	int			i;
	int			j;

	i = 1;
	j = 0;
	while (tab[i] != '\0')
	{
		j = 0;
		while (tab[i][j] != '\0')
		{
			if (!ft_isdigit(tab[i][j]))
				return_error(0, "Wrong room location");
			j++;
		}
		i++;
	}
	return (1);
}
