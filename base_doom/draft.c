/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:30:15 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/11 20:59:16 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int					draft(t_env *env)
{
	printf("curseur libre\n");
	return (SUCCESS);
}

int					create_point(t_env *env)
{
	printf("create point\n");
	env->editor.start_line = env->editor.cursor;
	printf("refresh start_line !\n");
	env->editor.draw_on = TRUE;
	return (SUCCESS);
}

int					draw(t_env *env)
{
	printf("draw line\n");
	if (env->editor.draw_on == TRUE)
		draw_line(env);
	return (SUCCESS);
}

int					generate_line(t_env *env)
{
	return (SUCCESS);
}
