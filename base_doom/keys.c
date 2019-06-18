/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 13:52:44 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/08 16:01:09 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void 		activate_keyboard(t_env *env, int keycode)
{
	t_keys	*k;

	k = &env->keys;
	if (keycode == KEY_W)
		env->keys.top = ON;
	if (keycode == KEY_S)
		k->bottom = ON;
	if (keycode == KEY_A)
		k->left_side = ON;
	if (keycode == KEY_D)
		k->right_side = ON;
}

void 		disable_keyboard(t_env *env, int keycode)
{
	t_keys	*k;

	k = &env->keys;
	if (keycode == KEY_W)
		k->top = OFF;
	else if (keycode == KEY_S)
		k->bottom = OFF;
	else if (keycode == KEY_A)
		k->left_side = OFF;
	else if (keycode == KEY_D)
		k->right_side = OFF;
}

void 		activate_mouse(t_env *env, int button)
{
	t_keys	*k;

	k = &env->keys;
	if (button == BUTTON_LEFT)
		k->left_mouse = ON;
	else if (button == BUTTON_RIGHT)
		k->right_mouse = ON;
}

void 		disable_mouse(t_env *env, int button)
{
	t_keys	*k;

	k = &env->keys;
	if (button == BUTTON_LEFT)
		k->left_mouse = OFF;
	else if (button == BUTTON_RIGHT)
		k->right_mouse = OFF;
}
