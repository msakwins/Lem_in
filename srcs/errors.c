/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakwins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 19:17:34 by msakwins          #+#    #+#             */
/*   Updated: 2017/10/10 21:04:52 by msakwins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		check_errors(t_env *env)
{
	env->start_found = 1;
}

void		return_error(int i, char *error)
{
	ft_putstr(RED"Error: "NOP);
	ft_putstr(error);
	if (i == 1)
		ft_putendl(CYAN" (Syntax) "NOP);
	if (i == 0)
		ft_putendl(CYAN" (Unknown) "NOP);
	exit(42);
}
