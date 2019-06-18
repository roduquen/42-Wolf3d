/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 14:03:23 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/11 16:50:17 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void 			change_automate(t_env *env, int automate, int state)
{
	t_automaton	*a;
	t_state		*start;

	env->current_automate = automate;
	a = env->automatons[automate];
	start = a->states[state];
	a->current_state = start;
	env->automatons[automate] = a;
}

void			add_transition(t_state *src, t_state *dest, int state)
{
	src->next_states[state] = dest;
}

t_state			*create_state(t_automaton *a, int type, t_pf *traitement)
{
	t_state		*state;
	t_state		**next;

	state = (t_state*)malloc(sizeof(t_state));
	if (state == NULL)
		return (NULL);
	ft_memset(state, 0, sizeof(t_state));
	next = (t_state**)malloc(sizeof(t_state*) * (NB_STATES + 1));
	if (next == NULL)
		return (NULL);
	ft_memset(next, 0, sizeof(t_state*) * (NB_STATES + 1));
	a->states[a->nb_states++] = state;
	state->next_states = next;
	state->pf = traitement;
	state->type = type;
	return (state);
}

t_automaton		*create_automaton(void *data)
{
	t_automaton	*a;

	a = (t_automaton*)malloc(sizeof(t_automaton));
	if (a == NULL)
		return (NULL);
	ft_memset(a, 0, sizeof(t_automaton));
	a->data = data;
	return (a);
}

t_state			*change_state(t_automaton *a)
{
	t_state		*current;

	current = a->current_state;
	current = current->next_states[current->pf((t_env*)a->data)];
	a->current_state = current;
	return (current);
}

int				run_automaton(t_automaton *a)
{
	t_state		*current;
	int  		iteration;

	iteration = 1;
	current = a->current_state;
	while (current && iteration--)
		current = change_state(a);
	if (current == NULL)
		return (change);
	return (42);
}
