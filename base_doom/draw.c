/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:29 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/11 21:07:12 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		plot(char *img, int x, int y)
{
	if (x < 0 || y < 0)
		return ;
	if (!((x < WIDTH) && (y < HEIGHT)))
		return ;
	*(img + x * 4 + y * WIDTH * 4) = (char)255;
	*(img + x * 4 + y * WIDTH * 4 + 1) = (char)255;
	*(img + x * 4 + y * WIDTH * 4 + 2) = (char)255;
}

static void		put_pixels(char *img, t_point *pc, t_point *q, int *d)
{
	int		e;
	int		ne;
	int		inc[2];

	inc[0] = (pc->x < q->x ? 1 : -1);
	inc[1] = (pc->y < q->y ? 1 : -1);
	e = (d[0] > d[1] ? d[0] / 2 : -d[1] / 2);
	while (!((pc->x == q->x) && (pc->y == q->y)))
	{
		plot(img, pc->x, pc->y);
		ne = e;
		if (ne > -d[0])
		{
			e -= d[1];
			pc->x += inc[0];
		}
		if (ne < d[1])
		{
			e += d[0];
			pc->y += inc[1];
		}
	}
}

void 			draw_line(t_env *env)
{
	char		*img;
	t_point		*click;
	t_point		*move;
	int			d[2];

	img = env->view.d_img;
	move = &env->editor.start_line;
	click = &env->editor.cursor;
	d[0] = abs(click->x - move->x);
	d[1] = abs(click->y - move->y);
	put_pixels(img, click, move, d);
}
