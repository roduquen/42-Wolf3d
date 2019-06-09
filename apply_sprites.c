/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 11:32:32 by mbenjell          #+#    #+#             */
/*   Updated: 2019/06/09 20:00:26 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void 				apply_sprites(t_thread *thread, int type, int i)
{
	t_wolf			*data;
	t_ray			*ray;
	unsigned int	*img;

	data = thread->data;
	img = data->texturetab;
}
