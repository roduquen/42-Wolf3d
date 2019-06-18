/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 13:36:17 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/11 18:27:06 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		add_states(t_automaton *a)
{
	create_state(a, cursor, draft);
	create_state(a, start_point, create_point);
	create_state(a, move_line, draw);
	create_state(a, add_line, generate_line);
}

static void		connect_states(t_automaton *a)
{
	t_state 	**states;

	states = a->states;
	// add_transition(states[cursor], states[cursor], cursor);
	// add_transition(states[cursor], states[start_point], start_point);
	// add_transition(states[start_point], states[move_line], start_point);
	// add_transition(states[move_line], states[add_line], start_point);
}

static int		compose(t_automaton *a)
{
	t_state		**states;

	states = (t_state**)malloc(sizeof(t_state*) * (NB_STATES + 1));
	if (states == NULL)
		return (ERROR);
	ft_memset(states, 0, sizeof(t_state*) * (NB_STATES + 1));
	a->states = states;
	return (SUCCESS);
}

void			editor(t_env *env)
{
	t_automaton	*a;
	t_state		*start;

	a = create_automaton(env);
	if (a == NULL)
		return ;
	compose(a);
	add_states(a);
	connect_states(a);
	start = a->states[cursor];
	a->current_state = start;
	a->type = trace;
	env->automatons[trace] = a;
}
