/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:57:09 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/11 18:45:18 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				key_press(int keycode, t_env *env)
{
	if (keycode == KEY_P)
	{
		env->activated[parser] = ON;
		change_automate(env, parser, file);
		return (SUCCESS);
	}
	else if (keycode == ESC)
		environment("Fin programme\n");
	env->peripheric = keyboard;
	env->current_event = press;
	activate_keyboard(env, keycode);
	change_automate(env, event, press);
	return (SUCCESS);
}

int				key_release(int keycode, t_env *env)
{
	env->peripheric = keyboard;
	env->current_event = release;
	disable_keyboard(env, keycode);
	change_automate(env, event, release);
	return (SUCCESS);
}

int				mouse_press(int button, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	env->peripheric = mouse;
	env->current_event = press;
	activate_mouse(env, button);
	change_automate(env, event, press);
	return (SUCCESS);
}

int				mouse_release(int button, int x, int y, t_env *env)
{
	t_point		*click;

	env->peripheric = mouse;
	env->current_event = release;
	disable_mouse(env, button);
	change_automate(env, event, release);
	return (SUCCESS);
}

int				mouse_move(int x, int y, t_env *env)
{
	t_point		*cursor;

	env->peripheric = mouse;
	env->current_event = move;
	cursor = &env->editor.cursor;
	cursor->x = x;
	cursor->y = y;
	change_automate(env, event, move);
	return (SUCCESS);
}
