/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 04:45:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/03 12:21:40 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "wolf.h"

/*static void	launch_ray_and_get_dist_and_orientation(t_thread *thread)
{
}*/

static void	draw_pixel_column(t_thread *thread)
{
	int				i;
	int				ret;
	unsigned int	*tab;

	i = thread->data->win_height / 3;
	tab = thread->data->texturetab;
//	launch_ray_and_get_dist_and_orientation(thread);
	while (i < thread->data->win_height)
	{
		ret = i * thread->data->win_width + thread->num;
		i++;
	}
}

static void	*calcul_ray_by_thread(void *data)
{
	t_thread		*thread;

	thread = (t_thread*)data;
	while (thread->num < thread->data->win_width)
	{
		thread->ray.angle = to_radian(thread->data->camera.alpha * thread->num
			- thread->data->camera.fov / 2.0 + thread->data->camera.angle);
		draw_pixel_column(thread);
		thread->num += NBR_THREAD;
	}
	pthread_exit(0);
}

int			raycasting(t_wolf *data)
{
	int			i;
	t_thread	thread[NBR_THREAD];

	i = 0;
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
