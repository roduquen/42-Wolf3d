/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:04:29 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/11 16:48:25 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int 			init_file(t_env *env)
{
	int			fd;

	printf("%s\n", env->file_name);
	fd = open(env->file_name, O_RDONLY);
	init_stream(&env->stream, fd);
	env->stream.fd = fd;
	return (header);
}

int 			build_data(t_env *env)
{
	(void)env;
	printf("fin parsing - debut traitement data\n");
	env->activated[parser] = OFF;
	return (change);
}
