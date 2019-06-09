/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_to_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:48:20 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/09 07:26:18 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	add_sprite_path(t_wolf *data)
{
	data->sprite_path[0] = "./textures/sprites/greenlight.bmp";
	data->sprite_path[1] = "./textures/sprites/pillar.bmp";
}

void		add_textures_path(t_wolf *data)
{
	data->texture_path[0] = "./textures/walls/blue_brick.bmp";
	data->texture_path[1] = "./textures/walls/greystone.bmp";
	data->texture_path[2] = "./textures/walls/wood.bmp";
	data->texture_path[3] = "./textures/walls/nazi_flag.bmp";
	data->texture_path[4] = "./textures/walls/prison_door.bmp";
	data->texture_path[5] = "./textures/walls/skull_prison_door.bmp";
	data->texture_path[6] = "./textures/walls/eagle_nazi_wood.bmp";
	data->texture_path[7] = "./textures/walls/eagle_nazi.bmp";
	data->texture_path[8] = "./textures/walls/hitler_greystone.bmp";
	data->texture_path[9] = "./textures/walls/hitler_wood.bmp";
	data->texture_path[10] = "./textures/walls/wall_ascensor.bmp";
	data->texture_path[11] = "./textures/walls/down_ascensor.bmp";
	data->texture_path[12] = "./textures/walls/door_slide.bmp";
	add_sprite_path(data);
}
