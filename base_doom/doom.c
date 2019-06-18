/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:27:10 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/11 16:50:23 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int 				end_programme(void *env)
{
	(void)env;
	exit(SUCCESS);
}

void 				environment(char *s)
{
	static t_env 	env;

	(void)env;
	printf("%s\n", s);
	exit(SUCCESS);
}

int 				run_programme(t_env *env)
{
	static int 		current = parser;
	int 			action;

	action = run_automaton(env->automatons[env->current_automate]);
	if (action == change)
	{
		current = (current + 1) % (change - parser);
		if (env->activated[current] == ON)
			change_automate(env, current, file | silent | cursor);
	}
	return (SUCCESS);
}

int					main(int ac, char **av)
{
	t_env 			env;

	if (ac != 2)
		return (ERROR);
	ft_memset(&env, 0, sizeof(t_env));
	env.file_name = av[1];
	env.mode = mode_editor;
	parsing(&env);
	manage_event(&env);
	init_view(&env);
	editor(&env);
	env.activated[parser] = ON;
	env.activated[event] = ON;
	env.activated[trace] = ON;
	change_automate(&env, parser, file);
	set_events(&env);
	return (SUCCESS);
}
