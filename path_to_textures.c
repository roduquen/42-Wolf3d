/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_to_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 01:48:20 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/09 13:57:45 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	add_sprite_path(t_wolf *data)
{
	data->sprite_path[0] = "./textures/sprites/greenlight.bmp";
	data->sprite_path[1] = "./textures/sprites/pillar.bmp";
}

static void	add_new_game_menu_path(t_wolf *data)
{
	data->menu_path[31] = "./textures/menu/new_game_menu/new_game_page_1.bmp";
	data->menu_path[32] = "./textures/menu/new_game_menu/new_game_page_2.bmp";
	data->menu_path[33] = "./textures/menu/new_game_menu/new_game_page_3.bmp";
	data->menu_path[34] = "./textures/menu/new_game_menu/new_game_page_4.bmp";
	data->menu_path[35] = "./textures/menu/new_game_menu/new_game_page_5.bmp";
	data->menu_path[36] = "./textures/menu/new_game_menu/new_game_page_6.bmp";
	data->menu_path[37] = "./textures/menu/new_game_menu/new_game_page_7.bmp";
	data->menu_path[38] = "./textures/menu/control_menu/control_page_1.bmp";
	data->menu_path[39] = "./textures/menu/control_menu/control_page_2.bmp";
	data->menu_path[40] = "./textures/menu/sound_menu/sound_page_1.bmp";
	data->menu_path[41] = "./textures/menu/sound_menu/sound_page_2.bmp";
}

static void	add_read_menu_path(t_wolf *data)
{
	data->menu_path[9] = "./textures/menu/read_menu/read_page_1.bmp";
	data->menu_path[10] = "./textures/menu/read_menu/read_page_2.bmp";
	data->menu_path[11] = "./textures/menu/read_menu/read_page_3.bmp";
	data->menu_path[12] = "./textures/menu/read_menu/read_page_4.bmp";
	data->menu_path[13] = "./textures/menu/read_menu/read_page_5.bmp";
	data->menu_path[14] = "./textures/menu/read_menu/read_page_6.bmp";
	data->menu_path[15] = "./textures/menu/read_menu/read_page_7.bmp";
	data->menu_path[16] = "./textures/menu/read_menu/read_page_8.bmp";
	data->menu_path[17] = "./textures/menu/read_menu/read_page_9.bmp";
	data->menu_path[18] = "./textures/menu/read_menu/read_page_10.bmp";
	data->menu_path[19] = "./textures/menu/read_menu/read_page_11.bmp";
	data->menu_path[20] = "./textures/menu/read_menu/read_page_12.bmp";
	data->menu_path[21] = "./textures/menu/read_menu/read_page_13.bmp";
	data->menu_path[22] = "./textures/menu/read_menu/read_page_14.bmp";
	data->menu_path[23] = "./textures/menu/read_menu/read_page_15.bmp";
	data->menu_path[24] = "./textures/menu/read_menu/read_page_16.bmp";
	data->menu_path[25] = "./textures/menu/read_menu/read_page_17.bmp";
	data->menu_path[26] = "./textures/menu/read_menu/read_page_18.bmp";
	data->menu_path[27] = "./textures/menu/read_menu/read_page_19.bmp";
	data->menu_path[28] = "./textures/menu/read_menu/read_page_20.bmp";
	data->menu_path[29] = "./textures/menu/read_menu/read_page_21.bmp";
	data->menu_path[30] = "./textures/menu/read_menu/read_page_22.bmp";
}

static void	add_menu_path(t_wolf *data)
{
	data->menu_path[0] = "./textures/menu/wolf_start.bmp";
	data->menu_path[1] = "./textures/menu/new_game_1.bmp";
	data->menu_path[2] = "./textures/menu/sound_1.bmp";
	data->menu_path[3] = "./textures/menu/control_1.bmp";
	data->menu_path[4] = "./textures/menu/load_game_1.bmp";
	data->menu_path[5] = "./textures/menu/graphic_detail_1.bmp";
	data->menu_path[6] = "./textures/menu/read_this_1.bmp";
	data->menu_path[7] = "./textures/menu/view_scores_1.bmp";
	data->menu_path[8] = "./textures/menu/quit_1.bmp";
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
	add_menu_path(data);
	add_read_menu_path(data);
	add_new_game_menu_path(data);
}
