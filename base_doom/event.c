/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 13:06:58 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/07 14:45:13 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		add_states(t_automaton *a)
{
	create_state(a, silent, on_silent);
	create_state(a, press, on_click);
	create_state(a, release, on_release);
	create_state(a, move, on_move);
}

static void		connect_states(t_automaton *a)
{
	t_state 	**states;

	states = a->states;
	add_transition(states[silent], states[silent], silent);
	add_transition(states[press], states[silent], silent);
	add_transition(states[release], states[silent], silent);
	add_transition(states[move], states[silent], silent);
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

void 			manage_event(t_env *env)
{
	t_automaton	*a;
	t_state		*start;

	a = create_automaton(env);
	if (a == NULL)
		return ;
	compose(a);
	add_states(a);
	connect_states(a);
	start = a->states[silent];
	a->current_state = start;
	a->type = event;
	env->automatons[event] = a;
}
