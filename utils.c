/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 13:45:50 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/15 21:36:17 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	fill_map(t_wolf *data, int size, char *tmp, int i)
{
	int		actual_map;

	actual_map = 0;
	while (i < size)
	{
		if (i % data->map_width == 0 || i % data->map_width
			== data->map_width - 2)
			tmp[i++] = 'a';
		else if (i % data->map_width == data->map_width - 1)
		{
			tmp[i++] = '\n';
			if (data->map[actual_map])
				actual_map++;
		}
		else if (data->map[actual_map] && data->map[actual_map] != '\n')
			tmp[i++] = data->map[actual_map++];
		else
			tmp[i++] = 'a';
	}
	tmp[i] = 0;
}

void	*calcul_ray_by_thread(void *data)
{
	t_thread		*thread;

	thread = (t_thread*)data;
	while (thread->num < WIDTH)
	{
		thread->ray.camx = 2 * thread->num / (double)WIDTH - 1;
		thread->ray.direction.x = thread->data->camera.direction.x
			+ thread->data->camera.plane.x * thread->ray.camx;
		thread->ray.direction.y = thread->data->camera.direction.y
			+ thread->data->camera.plane.y * thread->ray.camx;
		thread->ray.hit = 0;
		draw_pixel_column(thread);
		if (thread->num >= WIDTH / 2 - 16 * BLOCK && thread->num
			< WIDTH / 2 + 16 * BLOCK)
			add_weapon_to_screen(thread);
		thread->num += NBR_THREAD;
	}
	return (data);
	pthread_exit(0);
}

void	add_weapon_to_screen(t_thread *thread)
{
	int				i;
	int				j;
	int				k;
	unsigned int	color;

	i = HEIGHT - WIDTH * 11 / 120 - 32 * BLOCK;
	j = 64 * 384 * 7 + thread->num / (BLOCK / 2) + 40 + thread->data->shot;
	k = 0;
	color = ((unsigned int*)thread->data->surfaces[TEXTURE_NB + 2]->pixels)[0];
	while (i < HEIGHT - BLOCK * 11)
	{
		if (((unsigned int*)thread->data->surfaces[TEXTURE_NB + 2]->pixels)[j]
			!= color)
			thread->data->texturetab[i * WIDTH + thread->num] =
				((unsigned int*)thread->data->surfaces[TEXTURE_NB + 2]->pixels)
				[j];
		k++;
		if (k % (BLOCK / 2) == 0)
			j += 384;
		i++;
	}
}

void	add_hud_blocks(t_thread *thread, int i, int ret)
{
	if (thread->num >= 96 * BLOCK && thread->num <= 98 * BLOCK
			&& i == HEIGHT - 5 * BLOCK - WIDTH / 360)
		thread->data->texturetab[ret] = 0xFFFFFF;
	else if (thread->num != 12 * BLOCK && thread->num != 36 * BLOCK
			&& thread->num != 48 * BLOCK && thread->num != 60 * BLOCK
			&& thread->num != 78 * BLOCK && thread->num != 96 * BLOCK
			&& thread->num != 98 * BLOCK)
		thread->data->texturetab[ret] = thread->data->background[i];
	else
		thread->data->texturetab[ret] = 0xFFFFFF;
}
