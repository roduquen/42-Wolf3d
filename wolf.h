/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 00:25:42 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/07 15:03:41 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <SDL.h>
# include <pthread.h>

# define WIN_WIDTH	2560
# define WIN_HEIGHT	1440
# define CAMERA_FOV	60
# define NBR_THREAD	4
# define BLOCK_SIZE 32

# define CAMERA_RIGHT (1)
# define CAMERA_LEFT (1 << 1)
# define CAMERA_FRONT (1 << 2)
# define CAMERA_BACK (1 << 3)

typedef struct	s_vec2d
{
	double		x;
	double		y;
}				t_vec2d;

typedef struct	s_camera
{
	t_vec2d			position;
	t_vec2d			direction;
	t_vec2d			plane;
	double			hitbox;
	double			angle;
	double			angle_speed;
	double			move_speed;
	double			ray_length;
	double			fov;
	double			alpha;
	unsigned int	key;
}				t_camera;

typedef struct	s_wolf
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
	double			spacing;
	SDL_Surface		*surfaces[6];
	SDL_Texture		*walls[4];
	char			**board;
}				t_wolf;

typedef struct	s_ray
{
	t_vec2d		direction;
	double		camx;
	int			x_map;
	int			y_map;
	t_vec2d		side_dist;
	double		x_wall;
	double		x_tex;
	double		orto;
	t_vec2d		delta;
	t_vec2d		step;
	int			side;
	int			hit;
	int			height;
}				t_ray;

typedef struct	s_thread
{
	t_wolf		*data;
	int			num;
	t_ray		ray;
	pthread_t	thread;
}				t_thread;

/*
** INITIALISATION && LEAVE
*/

int				init_sdl_and_program(t_wolf *data);
int				leave_sdl_and_program(t_wolf *data, int type);
int				load_textures(t_wolf *data);
int				parsing_maps(t_wolf *data, char *path);
void			fill_map(t_wolf *data, int size, char *tmp, int i);

/*
** COMMANDS
*/

int				commands(t_wolf *data);
void			camera_downkey_event(t_wolf *data);
void			camera_upkey_event(t_wolf *data);
void			camera_mouse_event(t_wolf *data);
void			camera_carry_event(t_wolf *data, t_vec2d tmp);

/*
** MATHS
*/

double			to_radian(double degrees);
t_vec2d			vec2d_sub(t_vec2d a, t_vec2d b);
t_vec2d			vec2d_scalar(t_vec2d a, double scalar);
t_vec2d			vec2d_add(t_vec2d a, t_vec2d b);
t_vec2d			vec2d_unit(t_vec2d a);
t_vec2d			vec2d_rotate(t_vec2d a, double angle);
t_vec2d			vec2d(double x, double y);

/*
** RAYCASTING
*/

int				raycasting(t_wolf *data);
void			*calcul_ray_by_thread(void *data);
void			draw_pixel_column(t_thread *thread);

#endif