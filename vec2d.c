/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 04:36:21 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/15 21:16:12 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>

t_vec2d		vec2d_add(t_vec2d a, t_vec2d b)
{
	return ((t_vec2d){a.x + b.x, a.y + b.y});
}

t_vec2d		vec2d_scalar(t_vec2d a, double scalar)
{
	return ((t_vec2d){a.x * scalar, a.y * scalar});
}

t_vec2d		vec2d_sub(t_vec2d a, t_vec2d b)
{
	return ((t_vec2d){a.x - b.x, a.y - b.y});
}

t_vec2d		vec2d_unit(t_vec2d a)
{
	double		norme;

	norme = sqrt(a.x * a.x + a.y * a.y);
	return ((t_vec2d){a.x / norme, a.y / norme});
}

t_vec2d		vec2d_rotate(t_vec2d a, double angle)
{
	double		cosinus;
	double		sinus;

	cosinus = cos(angle);
	sinus = sin(angle);
	return ((t_vec2d){a.x * cosinus - a.y * sinus, a.x * sinus
		+ a.y * cosinus});
}
