/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:50:24 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/06 20:21:24 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		add_states(t_automaton *a)
{
	create_state(a, file, init_file);
	create_state(a, header, extract_header);
	create_state(a, level, extract_header);
	create_state(a, player, extract_header);
	create_state(a, map, extract_map);
	create_state(a, sector, extract_sector);
	create_state(a, texture, extract_header);
	create_state(a, data, build_data);
}

static void		connect_states(t_automaton *a)
{
	t_state 	**states;

	states = a->states;
	add_transition(states[file], states[header], header);
	add_transition(states[header], states[header], header);
	add_transition(states[header], states[map], map);
	add_transition(states[map], states[header], header);
	add_transition(states[header], states[level], level);
	add_transition(states[header], states[player], player);
	add_transition(states[header], states[sector], sector);
	add_transition(states[sector], states[header], header);
	add_transition(states[header], states[texture], texture);
	add_transition(states[header], states[data], data);
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

void			parsing(t_env *env)
{
	t_automaton	*a;
	t_state		*start;

	a = create_automaton(env);
	if (a == NULL)
		return ;
	compose(a);
	add_states(a);
	connect_states(a);
	start = a->states[file];
	a->current_state = start;
	a->type = parser;
	env->automatons[parser] = a;
}
