/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 14:01:49 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/11 21:02:58 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int  		on_silent(t_env *env)
{
	static int i = 0;
	(void)env;

	if (i++ > 100)
	{
		printf("Rendu.................\n");
		i = 0;
	}
	// printf("left mouse : %d\n", env->keys.left_mouse);
	// draw_line(env);
	update_view(env);
	return (SUCCESS);
}

int  		on_click(t_env *env)
{
	(void)env;

	if (env->mode == mode_editor)
		if (env->keys.left_mouse == 1)
			change_automate(env, trace, start_point);
	return (SUCCESS);
}

int  		on_release(t_env *env)
{
	(void)env;

	return (SUCCESS);
}

int  		on_move(t_env *env)
{
	(void)env;
	// printf("MOVE == periph (%d)\n", env->peripheric);
	change_automate(env, trace, move_line);
	return (SUCCESS);
}
