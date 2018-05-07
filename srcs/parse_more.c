/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakwins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 19:51:54 by msakwins          #+#    #+#             */
/*   Updated: 2017/10/10 22:38:39 by msakwins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int				is_pipe(t_env *env, char **tab)
{
	if (tab_len(tab) == 2)
	{
		if (ft_strequ(tab[0], tab[1]))
			return_error(0, "Same room in pipe");
	}
	if (env->pipe_found == 0)
		parse_rooms_to_tab(env);
	env->pipe_found = 1;
	return (1);
}

int				is_room(char **tab, char *line)
{
	if (line[0] == 'L')
		return_error(1, "Cannot start with L");
	if (tab_len(tab) != 2 && (count_blanks(line) == 2))
		return (1);
	else
		return (0);
	return (0);
}

int				parse_comment(char *line)
{
	if (line[0] == '#' && line[1] != '#')
		return (0);
	return (0);
}

int				parse_start_end(t_env *env, char *line)
{
	if (ft_strequ("##start", line))
	{
		if (env->start_found == 1)
			return_error(1, "Start room already defined");
		env->start_found = 1;
	}
	else if (ft_strequ("##end", line))
	{
		if (env->end_found == 1)
			return_error(1, "End room already defined");
		env->end_found = 1;
	}
	else if (ft_strequ("##debug", line))
		env->debug = 1;
	return (0);
}

int				parse_cats(t_env *env, char *line)
{
	int			i;
	intmax_t	cats;

	i = 0;
	if (ft_strlen(line) > 12)
		return_error(1, "Less cats please");
	while (line[i])
	{
		if (!(ft_isdigit(line[i])))
			return_error(0, "Unvalid number of cats, what are you doing?");
		i++;
	}
	cats = ft_atoll(line);
	if (cats > 2147483647)
		return_error(1, "Can't have more than INT_MAX cats");
	if (cats == 0)
		return_error(0, "0 cats found");
	env->cats = cats;
	return (0);
}
