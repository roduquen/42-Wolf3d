/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 09:33:13 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/09 11:10:56 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <SDL.h>

void		init_events(t_wolf *data)
{
	if (data->options == MENU_QUIT)
		data->running = 0;
	else if (data->options == MENU_READ)
		data->state = 2;
	else if (data->options == MENU_NEW)
		data->state = 3;
}
