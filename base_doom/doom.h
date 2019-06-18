/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:25:54 by mbenjell          #+#    #+#             */
/*   Updated: 2019/05/11 18:58:47 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "minilibx/mlx.h"

#include <stdio.h>
#include <limits.h>

# define TITLE				"Doom Nukem"
# define WIDTH 				1200
# define HEIGHT				1200
# define ESC				53

# define KEY_PRESS			2
# define KEY_RELEASE		3
# define MOUSE_PRESS		4
# define MOUSE_RELEASE		5
# define MOUSE_MOVE			6
# define EXPOSE_EVENT		12
# define CLOSE_EVENT		17

# define TOP				126
# define BOTTOM				125
# define LEFT				123
# define RIGHT				124
# define LEFT_SIDE			0
# define RIGHT_SIDE			2

# define BUTTON_LEFT			1
# define BUTTON_RIGHT			2
# define BUTTON_OTHER			3
# define BUTTON_SCROLLUP		4
# define BUTTON_SCROLLDOWN		5

# define KEY_P			35
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_Z			6
# define KEY_R			15
# define KEY_C			8
# define KEY_G			5
# define KEY_K			40
# define KEY_L			37
# define KEY_M			41
# define KEY_N			45
# define KEY_O			31
# define KEY_B			11
# define KEY_MINUS		27
# define KEY_EQUAL		24
# define KEY_TAB		48
# define KEY_BACKQUOTE	50
# define KEY_LCONTROL	256
# define KEY_RCONTROL	269
# define KEY_LALT		261
# define KEY_RALT		262
# define KEY_LSHIFT		257
# define KEY_RSHIFT		258
# define KEY_LOS		259
# define KEY_ROS		260
# define KEY_SPACE		49
# define KEY_RETURN		36
# define KEY_DELETE		51
# define KEY_SUPPRESS	117
# define KEY_UP			126
# define KEY_LEFT		123
# define KEY_DOWN		125
# define KEY_RIGHT		124
# define KEY_ESCAPE		53
# define KEY_NUM0		82
# define KEY_NUM1		83
# define KEY_NUM2		84
# define KEY_NUM3		85
# define KEY_NUM4		86
# define KEY_NUM5		87
# define KEY_NUM6		88
# define KEY_NUM7		89
# define KEY_NUM8		91
# define KEY_NUM9		92
# define KEY_NUMPLUS	69
# define KEY_NUMMINUS	78
# define KEY_PAGEUP		116
# define KEY_PAGEDOWN	121
# define KEY_HOME		115
# define KEY_END		119
# define KEY_0			29
# define KEY_1			18
# define KEY_2			19
# define KEY_3			20
# define KEY_4			21
# define KEY_5			23
# define KEY_6			22
# define KEY_7			26
# define KEY_8			28
# define KEY_9			25

# define SPACE				"\n\t "

# define SUCCESS			0
# define ERROR				-1

# define TRUE				1
# define FALSE				0

# define ON					1
# define OFF				0

# define BUFFER_SIZE		4096

typedef struct				s_stream
{
	char 					*file_name;
	int						fd;
	char					buff[BUFFER_SIZE];
	int						i;
	int						nread;
}							t_stream;

/**							LIBFT 							**/

void						*ft_memset(void *b, int c, size_t len);
void						*ft_memcpy(void *dst, const void *src, size_t n);
void						*ft_memchr(const void *s, int c, size_t n);
void						*ft_memalloc(size_t size);
void						ft_memdel(void **ap);
size_t						ft_strlen(const char *s);
char						*ft_strchr(const char *s, int c);
int							ft_strequ(const char *s1, const char *s2);

/**							STREAM 							**/

int							init_stream(t_stream *st, int fd);
int							ft_getchar(t_stream *s);
int							ft_getc(t_stream *s);
int							flusher(t_stream *s);
int							skip_space(t_stream *s);
int							fts_equal(t_stream *stream, char *s);
int							stream_to_buff(t_stream *s, char *buff);

/**							PARSING 							**/

typedef enum				e_block
{
	file,
	header,
	level,
	player,
	map,
	sector,
	texture,
	data
}							t_block;

/**							EDITOR 							**/

typedef enum 				e_mode
{
	mode_editor,
	mode_game
}							t_mode;

typedef struct s_env		t_env;

typedef struct				s_point
{
	int						x;
	int						y;
}							t_point;

typedef struct 				s_editor
{
	t_point 				cursor;
	t_point					start_line;
	int 					draw_on;
	int 					started;
}							t_editor;

void 						draw_line(t_env *env);

/**							EVENT 							**/

typedef enum 				e_event
{
	silent,
	press,
	release,
	move
}							t_event;

typedef enum 				e_peripheric
{
	keyboard,
	mouse
}							t_peripheric;

/**							AUTOMATE 						**/

# define NB_STATES			21
# define NB_AUTOMATES		4

typedef enum				e_automate
{
	parser,
	event,
	trace,
	change
}							t_automate;

typedef enum				e_draft
{
	cursor,
	start_point,
	move_line,
	add_line
}							t_draft;

typedef struct s_env 		t_env;
typedef int					t_pf(t_env *env);

typedef struct				s_state
{
	int						type;
	t_pf					*pf;
	struct s_state			**next_states;
}							t_state;

typedef struct				s_automaton
{
	int 					type;
	void					*data;
	t_state					**states;
	int						nb_states;
	t_state 				*current_state;
}							t_automaton;

void 			change_automate(t_env *env, int automate, int state);

/**							MLX 						**/

typedef struct				s_view
{
	void					*mlx;
	void					*win;
	void					*p_img;
	char					*d_img;
	char					*picture;
	char					*dynamic_picture;
}							t_view;

/**							EVENT 						**/

typedef struct				s_keys
{
	unsigned int 			top:1;
	unsigned int 			bottom:1;
	unsigned int 			left:1;
	unsigned int 			right:1;
	unsigned int 			left_side:1;
	unsigned int 			right_side:1;
	unsigned int			left_mouse:1;
	unsigned int			right_mouse:1;
}							t_keys;

/**							ENV 						**/

struct						s_env
{
	char 					*file_name;
	t_stream				stream;
	t_automaton				*automatons[NB_AUTOMATES];
	int						activated[NB_AUTOMATES];
	int 					current_automate;
	t_view					view;
	t_editor				editor;
	t_keys 					keys;
	int 					current_event;
	int 					peripheric;
	t_mode 					mode;
};

t_state				*create_state(t_automaton *a, int type, t_pf *traitement);
t_automaton			*create_automaton(void *data);
t_state				*change_state(t_automaton *a);
void 				add_transition(t_state *src, t_state *dest, int state);
int					run_automaton(t_automaton *a);

int 				build_data(t_env *env);
void				parsing(t_env *env);
int					extract_header(t_env *env);
int 				extract_map(t_env *env);
int 				extract_sector(t_env *env);

void 				manage_event(t_env *env);
int 				on_silent(t_env *env);
int					on_click(t_env *env);
int					on_release(t_env *env);
int					on_move(t_env *env);

void 				activate_keyboard(t_env *env, int keycode);
void 				disable_keyboard(t_env *env, int keycode);
void 				activate_mouse(t_env *env, int button);
void 				disable_mouse(t_env *env, int button);

/**							MLX 						**/

int					key_press(int keycode, t_env *env);
int					key_release(int keycode, t_env *env);
int					update_view(t_env *env);

int					mouse_press(int button, int x, int y, t_env *env);
int					mouse_release(int button, int x, int y, t_env *env);
int					mouse_move(int x, int y, t_env *env);

void				init_view(t_env *env);
int 				init_file(t_env *env);
void				set_events(t_env *env);

/**							PROGRAMME 						**/

void 				environment(char *s);
int 				run_programme(t_env *env);
int 				end_programme(void *env);

int					draft(t_env *env);
int					create_point(t_env *env);
int					draw(t_env *env);
int					generate_line(t_env *env);
void 				editor(t_env *env);

#endif
