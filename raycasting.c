/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 04:45:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/13 19:48:12 by roduquen         ###   ########.fr       */
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
		if (!ft_memchr(".0"
				, thread->data->board[thread->ray.x_map][thread->ray.y_map], 2))
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
	*min = ((double)WIN_HEIGHT - (double)thread->ray.height) / 2.0;
	if (*min < 0)
		*min = 0;
	*max = ((double)thread->ray.height + (double)WIN_HEIGHT) / 2.0;
	if (*max >= WIN_HEIGHT)
		*max = WIN_HEIGHT - 1;
	thread->ray.wall_size[thread->num % NBR_THREAD] = *max - *min;
	*i = -1;
}

int		add_minimap_color(t_thread *thread, int	i)
{
	int			pos[2];

	pos[0] = (int)thread->data->camera.position.x - thread->num / 16 + 8;
	pos[1] = (int)thread->data->camera.position.y - i / 16 + 8;
	if (pos[0] < 0 || pos[1] < 0)
		return (0x123456);
	if (pos[1] >= thread->data->map_width || pos[0] >= thread->data->map_height)
		return (0x123456);
	if ((thread->data->board[pos[0]][pos[1]] >= '1' && thread->data->board[pos[0]][pos[1]] <= '9') || thread->data->board[pos[0]][pos[1]] == 'k')
		return (0x7F7F7F);
	if (thread->data->board[pos[0]][pos[1]] != '.' && thread->data->board[pos[0]][pos[1]] != '0')
		return (0x654987);
	if (thread->data->board[pos[0]][pos[1]] == '0')
		return (0x789456);
	return (0);
}


void		draw_pixel_column(t_thread *thread)
{
	int					min;
	int					max;
	int					ret;
	int					i;

	launch_ray_and_get_dist_and_orientation(thread, &min, &max, &i);
	while (++i < WIN_HEIGHT)
	{
		ret = i * WIN_WIDTH + thread->num;
		if (thread->num < 16 || thread->num > WIN_WIDTH - 16 || i < 16 || i > WIN_HEIGHT - 16 || (i > WIN_HEIGHT - 166 && i < WIN_HEIGHT - 150))
			thread->data->texturetab[ret] = 0x555555;
		else if (thread->num == 16 || thread->num == WIN_WIDTH - 16 || i == 16 || i == WIN_HEIGHT - 16 || i == WIN_HEIGHT - 150 || i == WIN_HEIGHT - 166)
			thread->data->texturetab[ret] = 0;
		else if (thread->num < 255 && i < 255)
		{
			if (i >= 128 && i < 143 && thread->num >= 128 && thread->num < 143)
				thread->data->texturetab[ret] = 0xFF0000;
			else if (i % 16 != 15 && thread->num % 16 != 15 && i != 0 && thread->num != 0)
				thread->data->texturetab[ret] = add_minimap_color(thread, i);
			else
				thread->data->texturetab[ret] = 0xFFFFFF;
		}
		else if (i >= WIN_HEIGHT - 150)
		{
			if (thread->num >= 1536 && thread->num <= 1572
				&& i == WIN_HEIGHT - 83)
				thread->data->texturetab[ret] = 0xFFFFFF;
			else if (thread->num != 192 && thread->num != 576 && thread->num
				!= 768 && thread->num != 960 && thread->num != 1248
				&& thread->num != 1536 && thread->num != 1572)
				thread->data->texturetab[ret] = thread->data->background[i];
			else
				thread->data->texturetab[ret] = 0xFFFFFF;
		}
		else if (i >= min && i < max)
			apply_right_texture(thread, i, ret);
		else
			thread->data->texturetab[ret] = thread->data->background[i];
	}
}

int			raycasting(t_wolf *data)
{
	int			i;
	t_thread	thread[NBR_THREAD];

	i = 0;
	while (i < NBR_THREAD)
	{
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
