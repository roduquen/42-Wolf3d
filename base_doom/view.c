/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:51:45 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/10 22:25:48 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				update_view(t_env *env)
{
	t_view		*view;

	view = &env->view;
	mlx_put_image_to_window(view->mlx, view->win, view->p_img, 0, 0);
	return (SUCCESS);
}
