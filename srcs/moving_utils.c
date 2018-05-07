/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakwins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 19:03:41 by msakwins          #+#    #+#             */
/*   Updated: 2017/10/10 21:07:50 by msakwins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		continue_moving(t_engine *engine)
{
	int		index_last;
	int		end_index;
	int		i;

	i = 0;
	while (i < engine->nb_paths)
	{
		index_last = engine->nb_cats - i - 1;
		if (index_last < 0)
			return (0);
		end_index = engine->paths[engine->cats[index_last].path_chosen][0];
		if (engine->cats[index_last].cur_pos != end_index)
			return (1);
		i++;
	}
	return (0);
}

int		get_index_lower(int nb_paths, int cat_nb)
{
	int		tmp;

	tmp = cat_nb;
	while (tmp - nb_paths >= 0)
		tmp -= nb_paths;
	return (tmp);
}
