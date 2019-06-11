/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 11:32:32 by mbenjell          #+#    #+#             */
/*   Updated: 2019/06/11 16:29:14 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/**
** Te = d_a * To / d_m
** Te taille sprite en %
** d_a distance entre joueur et sprite
** To taille initiale sprite à distance minimale d_m du joueur
** thread->num : colonne
** i : ligne
**/

static int 			calcul_index(t_thread *thread, int line)
{
	int 			index;
	double			dist;
	int				start;
	int				end;
	t_vec2d			step;

	index = -1;
	step = thread->ray.step;
	dist = sqrt(step.x * step.x + step.y * step.y);
	start = (WIN_HEIGHT - (WIN_HEIGHT / dist)) / 2;
	end = (WIN_HEIGHT + (WIN_HEIGHT / dist)) / 2;
	// Condition sprite
	if (line > start && line < end)
		index =	abs(rand() % 100);
	thread->ray.sprite_dist = dist;
	return (index);
}


void 				apply_sprites(t_thread *thread, int type, int i)
{
	t_wolf			*data;
	// t_ray			*ray;
	unsigned int	*img;
	unsigned int 	*sprite;
	int 			index;

	data = thread->data;
	img = data->texturetab;
	sprite = (unsigned int*)thread->data->surfaces[type]->pixels;
	index = calcul_index(thread, i);
	if (index != -1)
		img[i * WIN_WIDTH + thread->num] = sprite[index];
}
