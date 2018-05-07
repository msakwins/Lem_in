/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakwins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 18:55:45 by msakwins          #+#    #+#             */
/*   Updated: 2017/10/10 21:11:32 by msakwins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int		print_cat(t_engine *engine, int index, int print_space)
{
	int index_of_room;
	int index_of_path;

	engine->cats[index].cur_pos += 1;
	index_of_path = engine->cats[index].path_chosen;
	index_of_room = engine->paths[index_of_path][engine->cats[index].cur_pos];
	if (print_space)
		ft_putchar(' ');
	ft_printf("%c%d%c%s", 'L', index + 1, '-',
			engine->rooms[index_of_room].name);
	return (1);
}

static int		maybe_print_cat(t_engine *engine, int index, int print_space)
{
	int		index_prev;

	if (engine->cats[index].cur_pos ==
			engine->paths[engine->cats[index].path_chosen][0])
		return (0);
	if (engine->cats[index].cur_pos != 1)
		return (print_cat(engine, index, print_space));
	index_prev = index - engine->nb_paths;
	if (index_prev < 0)
	{
		return (print_cat(engine, index, print_space));
	}
	if (engine->cats[index_prev].cur_pos ==
			engine->paths[engine->cats[index].path_chosen][0])
		return (print_cat(engine, index, print_space));
	if (engine->cats[index_prev].cur_pos != 1 &&
			engine->cats[index_prev].cur_pos != 2)
		return (print_cat(engine, index, print_space));
	return (0);
}

static void		move_cats(t_engine *engine)
{
	int		cat;
	int		print_space;

	while (continue_moving(engine))
	{
		cat = 0;
		print_space = 0;
		while (cat < engine->nb_cats)
		{
			print_space += maybe_print_cat(engine, cat, print_space);
			print_space = print_space > 1 ? print_space - 1 : print_space;
			cat++;
		}
		ft_putchar('\n');
	}
}

static t_cat	create_cat(int nb_paths, int cat_nb)
{
	t_cat	new_cat;
	int		i_path;
	int		best_path_found;
	int		index_lower;

	index_lower = get_index_lower(nb_paths, cat_nb);
	i_path = nb_paths;
	new_cat.cur_pos = 1;
	best_path_found = 0;
	while (i_path != 0 && best_path_found == 0)
	{
		if (index_lower % i_path == 0)
		{
			new_cat.path_chosen = i_path - 1;
			best_path_found = 1;
		}
		i_path--;
	}
	if (best_path_found == 0)
		new_cat.path_chosen = 0;
	return (new_cat);
}

void			init_cats(t_engine *engine)
{
	int		i;

	if (!(engine->cats = (t_cat *)malloc(sizeof(t_cat) * engine->nb_cats)))
		return ;
	i = 0;
	while (i < engine->nb_cats)
	{
		engine->cats[i] = create_cat(engine->nb_paths, i + 1);
		i++;
	}
	i = 0;
	if (engine->debug)
	{
		while (i < engine->nb_cats)
		{
			ft_printf("\e[95mCat %d take path %d\n", i + 1,
					engine->cats[i].path_chosen);
			i++;
		}
		ft_printf("\n");
	}
	move_cats(engine);
}
