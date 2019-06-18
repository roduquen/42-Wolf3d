/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:13:47 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/11 16:46:37 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		extract_word(t_stream *s)
{
	char 		buff[42];

	stream_to_buff(s, buff);
	if (ft_strequ(buff, "LEVEL") == TRUE)
		return (level);
	else if (ft_strequ(buff, "PLAYER") == TRUE)
		return (player);
	else if (ft_strequ(buff, "MAP") == TRUE)
		return (map);
	else if (ft_strequ(buff, "SECTOR") == TRUE)
		return (sector);
	else if (ft_strequ(buff, "TEXTURE") == TRUE)
		return (texture);
	return (ERROR);
}

static int 		parse_head(t_stream *s)
{
	int 		type_bloc;

	skip_space(s);
	if (fts_equal(s, "[--[") == FALSE)
		return (ERROR);
	skip_space(s);
	type_bloc = extract_word(s);
	skip_space(s);
	if (fts_equal(s, "]--]") == FALSE)
		return (ERROR);
	skip_space(s);
	return (type_bloc);
}

int 			extract_header(t_env *env)
{
	int			type_bloc;
	t_stream	*s;

	s = &(env->stream);
	type_bloc = parse_head(s);
	printf("extract_header : %d\n", type_bloc);
	if (type_bloc == ERROR)
		return (data);
	return (type_bloc);
}
