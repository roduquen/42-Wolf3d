/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 00:33:40 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/06 12:10:40 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <unistd.h>

int		main(int ac, char **av)
{
	t_wolf		data;

	if (ac != 2)
	{
		write(2, "Wolf3d : Usage : ./wolf3d [PATH/MAP]\n", 37);
		return (1);
	}
	ft_memset(&data, 0, sizeof(t_wolf));
	if (parsing_maps(&data, av[1]))
		return (1);
	if (init_sdl_and_program(&data))
		return (1);
	if (commands(&data))
		return (1);
	leave_sdl_and_program(&data, 0);
	return (0);
}
