/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 00:33:40 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/15 21:16:16 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <unistd.h>

int		main(void)
{
	t_wolf		data;

	ft_memset(&data, 0, sizeof(t_wolf));
	if (init_sdl_and_program(&data))
		return (1);
	if (commands(&data))
		return (1);
	leave_sdl_and_program(&data, 0);
	return (0);
}
