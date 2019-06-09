/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 04:45:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/09 07:24:59 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "wolf.h"

static void	init_and_compute_steps(t_thread *thread)
{
	if (thread->ray.direction.x < 0)
	{
		thread->ray.step.x = -1;
		thread->ray.side_dist.x = (thread->data->camera.position.x
				- thread->ray.x_map) * thread->ray.delta.x;
	}
	else
	{
		thread->ray.step.x = 1;
		thread->ray.side_dist.x = (thread->ray.x_map + 1.0
				- thread->data->camera.position.x) * thread->ray.delta.x;
	}
	if (thread->ray.direction.y < 0)
	{
		thread->ray.step.y = -1;
		thread->ray.side_dist.y = (thread->data->camera.position.y
				- thread->ray.y_map) * thread->ray.delta.y;
	}
	else
	{
		thread->ray.step.y = 1;
		thread->ray.side_dist.y = (thread->ray.y_map + 1.0
				- thread->data->camera.position.y) * thread->ray.delta.y;
	}
}

static void	step_loop(t_thread *thread)
{
	while (thread->ray.hit == 0)
	{
		if (thread->ray.side_dist.x < thread->ray.side_dist.y)
		{
			thread->ray.side_dist.x += thread->ray.delta.x;
			thread->ray.x_map += thread->ray.step.x;
			thread->ray.side = 0;
		}
		else
		{
			thread->ray.side_dist.y += thread->ray.delta.y;
			thread->ray.y_map += thread->ray.step.y;
			thread->ray.side = 1;
		}
		if (ft_strchr(WALLS
				, thread->data->board[thread->ray.x_map][thread->ray.y_map]))
			thread->ray.hit = 1;
	}
	if (thread->ray.side == 0)
		thread->ray.orto = (thread->ray.x_map - thread->data->camera.position.x
				+ (1 - thread->ray.step.x) / 2) / thread->ray.direction.x;
	else
		thread->ray.orto = (thread->ray.y_map - thread->data->camera.position.y
				+ (1 - thread->ray.step.y) / 2) / thread->ray.direction.y;
	thread->ray.height = (int)(thread->data->win_height / thread->ray.orto);
}

static void	launch_ray_and_get_dist_and_orientation(t_thread *thread
	, int *min, int *max, int *i)
{
	thread->ray.x_map = (int)thread->data->camera.position.x;
	thread->ray.y_map = (int)thread->data->camera.position.y;
	thread->ray.delta.x = fabs(1 / thread->ray.direction.x);
	thread->ray.delta.y = fabs(1 / thread->ray.direction.y);
	init_and_compute_steps(thread);
	step_loop(thread);
	*min = (thread->data->win_height - thread->ray.height) / 2;
	if (*min < 0)
		*min = 0;
	*max = (thread->ray.height + thread->data->win_height) / 2;
	if (*max >= thread->data->win_height)
		*max = thread->data->win_height - 1;
	*i = -1;
}

void		draw_pixel_column(t_thread *thread)
{
	int				min;
	int				max;
	int				ret;
	int				i;

	launch_ray_and_get_dist_and_orientation(thread, &min, &max, &i);
	while (++i < thread->data->win_height)
	{
		ret = i * thread->data->win_width + thread->num;
		if (i > min && i < max)
			apply_right_texture(thread, i);
		else if (i <= min)
			thread->data->texturetab[ret] = 0X87CEEB;
		else
			thread->data->texturetab[ret] = 0x828282;
	}
}

int			raycasting(t_wolf *data)
{
	int			i;
	t_thread	thread[NBR_THREAD];

	i = 0;
	ft_memset(data->texturetab, 0, data->win_width * data->win_height);
	while (i < NBR_THREAD)
	{
		ft_memset(&(thread[i]), 0, sizeof(t_thread));
		(thread[i]).data = data;
		(thread[i]).num = i;
		if (pthread_create(&(thread[i]).thread, NULL, (*calcul_ray_by_thread)
					, &(thread[i])) < 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < NBR_THREAD)
		pthread_join(thread[i++].thread, NULL);
	return (0);
}
