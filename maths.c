/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 04:36:21 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/15 21:15:28 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf.h"

double		to_radian(double degrees)
{
	return (M_PI * degrees / 180.0);
}

t_vec2d		vec2d(double x, double y)
{
	t_vec2d		vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}
