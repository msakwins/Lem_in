/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakwins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 19:54:21 by msakwins          #+#    #+#             */
/*   Updated: 2017/10/10 21:10:16 by msakwins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		init(t_env *env)
{
	env->fd = 0;
	env->cats = 0;
	env->nb_room = 0;
	env->start_found = 0;
	env->end_found = 0;
	env->pipe_found = 0;
	env->nb_line = 0;
	env->debug = 0;
	env->buffer = NULL;
	env->room = NULL;
}
