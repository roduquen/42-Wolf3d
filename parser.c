/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 01:19:18 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/05 19:46:31 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static int	check_if_well_formated(char *map)
{
	int		i;
	int		player;

	i = 0;
	player = 0;
	while (map[i])
	{
		if (map[i] == '>' || map[i] == '^' || map[i] == '<' || map[i] == 'v')
			player++;
		else if (map[i] != '\n' && map[i] != 'x' && map[i] != '.')
			return (1);
		i++;
	}
	if (player != 1)
		return (1);
	return (0);
}

static int	parse_file(int fd, t_wolf *data)
{
	int		ret;
	char	buffer[1];
	char	*translate;

	if (!(data->map = ft_strnew(2)))
		return (1);
	while ((ret = read(fd, buffer, 1)) == 1)
	{
		if (!(translate = (char*)malloc(sizeof(char)
						* (ft_strlen(data->map) + 3))))
			return (1);
		ft_strcpy(translate, data->map);
		free(data->map);
		translate[ft_strlen(translate) + 1] = 0;
		translate[ft_strlen(translate)] = buffer[0];
		data->map = translate;
		if (data->map[0] == 0)
			return (1);
		if (ft_strlen(data->map) > 10000)
			return (1);
	}
	return (ret);
}

static int	resize_map(t_wolf *data)
{
	int			i;
	int			actual_map;
	int			size;
	char		*tmp;

	i = 0;
	size = data->map_width * data->map_height;
	if (!(tmp = (char*)malloc(sizeof(char) * (size + 1))))
		return (1);
	while (i < data->map_width - 1)
		tmp[i++] = 'x';
	tmp[i++] = '\n';
	actual_map = 0;
	while (i < size)
	{
		if (i % data->map_width == 0 || i % data->map_width
			== data->map_width - 2)
			tmp[i++] = 'x';
		else if (i % data->map_width == data->map_width - 1)
		{
			tmp[i++] = '\n';
			if (data->map[actual_map])
				actual_map++;
		}
		else if (data->map[actual_map] && data->map[actual_map] != '\n')
			tmp[i++] = data->map[actual_map++];
		else
			tmp[i++] = 'x';
	}
	tmp[i] = 0;
	free(data->map);
	data->map = tmp;
	return (0);
}

static int	translate_map_to_rectangular_map(t_wolf *data)
{
	int		actual;
	int		i;

	i = 0;
	actual = 0;
	while (data->map[i])
	{
		if (data->map[i] == '\n')
		{
			if (data->map_width < i - actual)
				data->map_width = i - actual;
			actual = i;
			data->map_height++;
		}
		i++;
	}
	data->map_width += 2;
	data->map_height += 3;
	return (resize_map(data));
}

int			parsing_maps(t_wolf *data, char *path)
{
	int			fd;

	if ((fd = open(path, O_DIRECTORY)) != -1)
	{
		write(2, "A directory, hummm...\n", 22);
		return (leave_sdl_and_program(data, 1));
	}
	if ((fd = open(path, O_RDONLY)) <= 0)
	{
		write(2, "Something went wrong with the file\n", 35);
		return (leave_sdl_and_program(data, 1));
	}
	if (parse_file(fd, data) || !data->map)
	{
		write(2, "Something went wrong while reading file\n", 40);
		return (leave_sdl_and_program(data, 1));
	}
	if (check_if_well_formated(data->map)
		|| translate_map_to_rectangular_map(data))
	{
		write(2, "File is not correctly formated\n", 32);
		return (leave_sdl_and_program(data, 1));
	}
	return (0);
}
