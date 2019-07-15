/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 02:51:48 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/15 21:14:46 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>

static void	fill_bg_tab(int color[3], int i, t_wolf *data, double gradient)
{
	while (i < HEIGHT - 10 * WIDTH / 120)
	{
		gradient = ((double)i - ((double)HEIGHT / 2.0))
			/ ((double)HEIGHT / 2.0);
		color[0] = gradient * 0x82;
		data->background[i++] = color[0] | (color[0] << 8)
			| (color[0] << 16);
	}
	while (i < HEIGHT)
	{
		if (i == HEIGHT - 10 * WIDTH / 120)
			data->background[i++] = 0xFFFFFF;
		else
		{
			gradient = (double)(i - HEIGHT + 10 * WIDTH / 120)
				/ (double)HEIGHT * 5;
			color[2] = 0x1f - gradient * 0x1f;
			color[1] = 0x18 - gradient * 0x18;
			color[0] = 0xf0 - gradient * 0xf0;
			data->background[i++] = color[0] | (color[1] << 8)
			| (color[2] << 16);
		}
	}
}

void		full_background_tab(t_wolf *data)
{
	int			i;
	int			color[3];
	double		gradient;

	i = 0;
	while (i < HEIGHT / 2)
	{
		color[0] = 0x87;
		color[1] = 0xCE;
		color[2] = 0xEB;
		gradient = (double)i / (double)HEIGHT * 2.0;
		color[0] -= gradient * color[0];
		color[1] -= gradient * color[1];
		color[2] -= gradient * color[2];
		data->background[i++] = color[2] | (color[1] << 8)
		| (color[0] << 16);
	}
	gradient = 0;
	fill_bg_tab(color, i, data, gradient);
}
