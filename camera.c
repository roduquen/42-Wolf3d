/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:12:58 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/03 14:04:32 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		camera_carry_event(t_wolf *data)
{
	if (data->camera.key & CAMERA_FRONT)
		data->camera.position = vec2d_add(data->camera.position
				, data->camera.direction);
	if (data->camera.key & CAMERA_BACK)
		data->camera.position = vec2d_sub(data->camera.position
				, data->camera.direction);
	if (data->camera.key & CAMERA_LEFT)
		data->camera.position = vec2d_add(data->camera.position
				, vec2d_unit(vec2d_rotate(data->camera.direction
						, to_radian(90.0))));
	if (data->camera.key & CAMERA_RIGHT)
		data->camera.position = vec2d_add(data->camera.position
				, vec2d_unit(vec2d_rotate(data->camera.direction
						, to_radian(270.0))));
}

void		camera_downkey_event(t_wolf *data)
{
	if (data->event.key.keysym.sym == SDLK_d)
		data->camera.key |= CAMERA_RIGHT;
	else if (data->event.key.keysym.sym == SDLK_a)
		data->camera.key |= CAMERA_LEFT;
	else if (data->event.key.keysym.sym == SDLK_w)
		data->camera.key |= CAMERA_FRONT;
	else if (data->event.key.keysym.sym == SDLK_s)
		data->camera.key |= CAMERA_BACK;
}

void		camera_upkey_event(t_wolf *data)
{
	if (data->event.key.keysym.sym == SDLK_RIGHT)
		data->camera.key &= ~CAMERA_RIGHT;
	else if (data->event.key.keysym.sym == SDLK_LEFT)
		data->camera.key &= ~CAMERA_LEFT;
	else if (data->event.key.keysym.sym == SDLK_UP)
		data->camera.key &= ~CAMERA_FRONT;
	else if (data->event.key.keysym.sym == SDLK_DOWN)
		data->camera.key &= ~CAMERA_BACK;
}

void		camera_mouse_event(t_wolf *data)
{
	t_vec2d		vec;

	if (data->event.motion.xrel)
	{
		data->camera.angle += (data->event.motion.xrel / 10.0);
		if (data->camera.angle > 360)
			data->camera.angle -= 360;
		else if (data->camera.angle < 0)
			data->camera.angle += 360;
		vec.x = 1;
		vec.y = 0;
		data->camera.direction = vec2d_unit(vec2d_rotate(vec
				, to_radian(data->camera.angle)));
	}
}
