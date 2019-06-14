/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 00:25:42 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/13 19:28:49 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <SDL.h>
# include <pthread.h>

# define WIN_WIDTH	1280
# define WIN_HEIGHT	720
# define CAMERA_FOV	60
# define NBR_THREAD	4

# define TEXTURE_NB	13
# define SPRITE_NB	2
# define MENU_NB	42

# define MENU_NEW	1
# define MENU_SOUND	2
# define MENU_CONT	3
# define MENU_READ	6
# define MENU_QUIT	8

# define WALLS		"123456789abcdefghijklmx"

# define CAMERA_RIGHT (1)
# define CAMERA_LEFT (1 << 1)
# define CAMERA_FRONT (1 << 2)
# define CAMERA_BACK (1 << 3)


typedef struct	s_wolf		t_wolf;

typedef struct				s_vec2d
{
	double		x;
	double		y;
}							t_vec2d;

typedef struct				s_camera
{
	t_vec2d			position;
	t_vec2d			direction;
	t_vec2d			plane;
	double			hitbox;
	double			angle;
	double			angle_speed;
	double			move_speed;
	unsigned int	key;
}							t_camera;

typedef struct				s_ray
{
	t_vec2d		direction;
	double		camx;
	int			x_map;
	int			y_map;
	t_vec2d		side_dist;
	double		x_wall;
	int			x_tex;
	int			y_tex;
	double		orto;
	t_vec2d		delta;
	t_vec2d		step;
	int			side;
	int			hit;
	int			height;
}							t_ray;

typedef struct				s_thread
{
	t_wolf		*data;
	int			num;
	t_ray		ray;
	pthread_t	thread;
}							t_thread;

struct						s_wolf
{
	SDL_Texture		*texture;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	int				win_height;
	int				win_width;
	unsigned int	*texturetab;
	SDL_Event		event;
	SDL_bool		running;
	char			*map;
	int				map_width;
	int				map_height;
	t_camera		camera;
	SDL_Surface		*surfaces[TEXTURE_NB + SPRITE_NB];
	SDL_Texture		*menu[MENU_NB];
	char			*texture_path[TEXTURE_NB];
	char			*sprite_path[SPRITE_NB];
	char			*menu_path[MENU_NB];
	char			**board;
	int				state;
	int				options;
	int				actual_read;
	int				actual_new_game;
	int				actual_control;
	int				actual_sound;
	int				actual_floor;
	t_thread		thread[NBR_THREAD];
};

/*
** INITIALISATION && LEAVE
*/

int							init_sdl_and_program(t_wolf *data);
void						init_data_and_camera(t_wolf *data);
int							leave_sdl_and_program(t_wolf *data, int type);
void						add_textures_path(t_wolf *data);
int							load_textures(t_wolf *data);
int							parsing_maps(t_wolf *data, char *path);
void						fill_map(t_wolf *data, int size, char *tmp, int i);

/*
** COMMANDS
*/

int							commands(t_wolf *data);
void						camera_downkey_event(t_wolf *data);
void						camera_upkey_event(t_wolf *data);
void						camera_mouse_event(t_wolf *data);
void						camera_carry_event(t_wolf *data, t_vec2d tmp);
void						sdl_events_hook(t_wolf *data);
void						init_events(t_wolf *data);
void						init_game(t_wolf *data);
void						active_commands(t_wolf *data, t_vec2d pos);
void						init_floor_change(t_wolf *data);

/*
** GAME STATE
*/

int							game_running(t_wolf *data);
void						game_options_sound(t_wolf *data);
void						game_options_control(t_wolf *data);
void						game_options_new_game(t_wolf *data);
void						game_options_read(t_wolf *data);
void						game_init(t_wolf *data);
void						game_start(t_wolf *data);

/*
** MATHS
*/

double						to_radian(double degrees);
t_vec2d						vec2d_sub(t_vec2d a, t_vec2d b);
t_vec2d						vec2d_scalar(t_vec2d a, double scalar);
t_vec2d						vec2d_add(t_vec2d a, t_vec2d b);
t_vec2d						vec2d_unit(t_vec2d a);
t_vec2d						vec2d_rotate(t_vec2d a, double angle);
t_vec2d						vec2d(double x, double y);

/*
** RAYCASTING
*/

int							raycasting(t_wolf *data);
void						*calcul_ray_by_thread(void *data);
void						draw_pixel_column(t_thread *thread);
void						apply_textures(t_thread *thread, int type, int i);
void						apply_right_texture(t_thread *thread, int i);

/*
** UTILS
*/

void						frame_calculator(unsigned int actual);

#endif
