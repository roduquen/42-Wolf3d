/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 02:51:48 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/11 03:02:54 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		full_background_tab(t_wolf *data)
{
	int			i;
	int			color[3];
	double		gradient;

	i = 0;
	while (i < WIN_HEIGHT / 2)
	{
		color[0] = 0x87;
		color[1] = 0xCE;
		color[2] = 0xEB;
		gradient = (double)i / (double)WIN_HEIGHT * 2.0;
		color[0] -= gradient * color[0];
		color[1] -= gradient * color[1];
		color[2] -= gradient * color[2];
		data->background[i++] = color[2] | (color[1] << 8)
		| (color[2] << 16);
	}
	while (i < WIN_HEIGHT)
	{
		gradient = ((double)i - ((double)WIN_HEIGHT / 2.0))
			/ ((double)WIN_HEIGHT / 2.0);
		color[0] = gradient * 0x82;
		data->background[i++] = color[0] | (color[0] << 8)
			| (color[0] << 16);
	}
}
