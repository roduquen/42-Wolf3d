/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <roduquen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 01:19:18 by roduquen          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/06/09 19:08:07 by mbenjell         ###   ########.fr       */
=======
/*   Updated: 2019/06/09 19:50:30 by roduquen         ###   ########.fr       */
>>>>>>> aba6118a3f0feb948254069095102805f69ec9a5
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
		if (ft_strchr("><^v", map[i]))
			player++;
<<<<<<< HEAD
		else if (!ft_strchr("\nx.0abcdefghijklA", map[i]))
=======
		else if (!ft_strchr("\n.0abcdefghijkl", map[i]))
>>>>>>> aba6118a3f0feb948254069095102805f69ec9a5
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
	int			size;
	char		*tmp;

	i = 0;
	size = data->map_width * data->map_height;
	if (!(tmp = (char*)malloc(sizeof(char) * (size + 1))))
		return (1);
	while (i < data->map_width - 1)
		tmp[i++] = 'a';
	tmp[i++] = '\n';
	fill_map(data, size, tmp, i);
	free(data->map);
	data->map = tmp;
	if (!(data->board = ft_strsplit(data->map, '\n')))
		return (1);
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
	if (data->map_width < i - actual)
		data->map_width = i - actual;
	data->map_width += 3;
	data->map_height += 2 + (data->map[i - 1] == '\n' ? 0 : 1);
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
