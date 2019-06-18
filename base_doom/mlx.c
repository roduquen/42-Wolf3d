/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:36:03 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/06 14:57:37 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		init_view(t_env *e)
{
	int			bpp;
	int			s_l;
	int			endian;
	t_view		*v;

	v = &e->view;
	v->mlx = mlx_init();
	if (v->mlx == NULL)
		environment("ECHEC MLX");
	v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, TITLE);
	if (v->win == NULL)
		environment("ECHEC MLX");
	v->p_img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
	if (v->p_img == NULL)
		environment("ECHEC MLX");
	v->d_img = mlx_get_data_addr(v->p_img, &bpp, &s_l, &endian);
	if (v->d_img == NULL)
		environment("ECHEC MLX");
}

void		set_events(t_env *env)
{
	mlx_hook(env->view.win, KEY_PRESS, 0, key_press, env);
	mlx_hook(env->view.win, KEY_RELEASE, 0, key_release, env);
	mlx_hook(env->view.win, MOUSE_PRESS, 0, mouse_press, env);
	mlx_hook(env->view.win, MOUSE_RELEASE, 0, mouse_release, env);
	mlx_hook(env->view.win, MOUSE_MOVE, 0, mouse_move, env);
	mlx_hook(env->view.win, CLOSE_EVENT, 0, end_programme, env);
	mlx_loop_hook(env->view.mlx, run_programme, env);
	mlx_loop(env->view.mlx);
}
