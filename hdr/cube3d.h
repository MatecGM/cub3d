/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadelbes <gadelbes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 21:39:50 by mbico             #+#    #+#             */
/*   Updated: 2024/12/15 16:47:14 by gadelbes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "mlx.h"
# include <math.h>
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdint.h>
# include <sys/time.h>
# include <limits.h>

# include <coord.h>
# include <parsing.h>
# include <ssys.h>
# include <pthread.h>

# define WIDTH 1280
# define HEIGHT 720
# define PI 3.14159265359

# define RENDER_DISTANCE 12

# define MINIMAP_SIZE 100
# define RD_MM 8
# define SIZE_MM 150
# define PADDING_MM 45
# define RADIUS_MM 75

# define DOOR_OP_PATH_TXT "./txtr/door_open.png"
# define DOOR_CLS_PATH_TXT "./txtr/door_close.png"

# define SPEAKER_FRAME 10
# define SPEAKER_PATH "./txtr/speaker/speaker0.png"

typedef enum e_wall
{
	FLOOR,
	WALL,
	DOOR_CLS,
	DOOR_OP,
	SPEAKER_OFF,
	SPEAKER_ON,
}	t_wall;

typedef union u_argb
{
	uint32_t	argb;
	struct
	{
		uint8_t	a;
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
	};
}	t_argb;

//wall hit
typedef struct s_wh
{
	t_coord		hit;
	t_verif		face;
	t_dcoord	rpos;
}	t_wh;

typedef struct s_rc
{
	double	ay;
	double	ax;
	uint8_t	rd;
	t_coord	ray;
	t_coord	side_dist;
}		t_rc;

typedef struct s_texture
{
	t_dcoord	size;
	void		*img;

}	t_texture;

typedef struct s_anim_txtr
{
	t_texture	*speaker;
}	t_anim_txtr;

typedef struct s_map
{
	int8_t		**content;
	t_texture	*txt;
	t_anim_txtr	anim_txtr;
	t_dcoord	size;
	t_argb		floor;
	t_argb		sky;
}	t_map;

typedef struct s_player
{
	double		dir;
	double		old_dir;
	t_dcoord	mouse_init;
	t_coord		pos;
	double		move_speed;
	double		rot_speed;
	t_wall		target;
}	t_player;

typedef struct s_hud
{
	t_bool			rotate_mm;
	uint32_t		start_anim;
	uint32_t		frame_speaker;
	uint8_t			*mu_code;
	pthread_mutex_t	mumu_code;
	t_coord			*mu_stereo;
	pthread_mutex_t	mumu_stereo;
}	t_hud;

typedef struct s_fps
{
	uint32_t	old_time;
	uint32_t	time;
	double		fps;
}	t_fps;

typedef struct s_data
{
	__uint128_t	input;
	t_rc		rc;
	t_parse		*psg;
	t_hud		hud;
	t_fps		fps;
	void		*mlx;
	void		*win;
	void		*img;
	t_player	player;
	int32_t		**screen;
	t_map		map;
}				t_data;

typedef struct s_gc
{
	void		*adr;
	t_bool		istab;
	struct s_gc	*next;
}	t_gc;

void			displaying(t_data *data);
void			print_line(t_data *data, t_dcoord p1, \
				t_dcoord p2, t_argb color);
void			circle_mm(t_data *data, t_coord center, \
				uint32_t r, t_argb color);
t_wh			dda(t_data *data, double dir);
void			put_pixel_inscreen(t_data *data, int x, int y, t_argb color);
void			display_rc(t_data *data);

t_bool			check_approx(double nb1, double nb2, int approx);
void			display_clear(t_data *data);
void			display_screen(t_data *data, int32_t **screen);
void			display_crosshair(t_data *data);
t_dcoord		ft_map_len(int8_t **map);
t_argb			get_png_pixel(t_data *data, t_texture txt, \
				double x, t_dcoord ptr);

t_bool			get_input_state(__uint128_t input, int kc);
int				keydown(int kc, void *d);
int				keyup(int kc, void *d);
int				key_action(t_data *data);
int				mousedown(int kc, void *d);
int				mouseup(int kc, void *d);
void			mouse_action(t_data *data);
void			hud_action(t_data *data, int kc);
void			interact_system(t_data *data, int kc);
void			move(t_data *data);

t_coord			dda_x(t_data *data, double dir);
t_coord			dda_y(t_data *data, double dir);

t_bool			init_data(t_data *data, t_parse *psg, uint8_t *mu_code, \
				t_coord *mu_stereo);
int32_t			**init_screen(void);

t_bool			put_pixel_on_mm(uint32_t **frame_mm, int32_t x, \
				int32_t y, uint32_t color);
uint32_t		**init_mm(void);
void			display_mm_on_screen(t_data *data, uint32_t **frame);
void			display_mm(t_data *data);
void			print_line_mm(uint32_t **frame, t_dcoord p1, \
				t_dcoord p2, t_argb color);
uint32_t		**rotate_mm(uint32_t **src, double dir);

t_argb			all_text_rel_color(t_data *data, t_wh wh, \
				t_dcoord ptr, t_texture *txt);
t_argb			mono_text_rel_color(t_data *data, t_wh wh, \
				t_dcoord ptr, t_texture txt);
t_argb			texture_rel_color(t_data *data, t_wh wh, t_dcoord ptr);

void			fps_counter(t_data *data);
unsigned int	time_now(void);
t_dcoord		get_cdvec(double dir);
void			close_safe(t_data *data);

uint8_t			mutex_checker(uint8_t *nb, pthread_mutex_t *mutex);
void			mutex_set_int(uint8_t *var, uint8_t new, \
				pthread_mutex_t *mutex);
void			mutex_set_coord(t_coord *var, t_coord new, \
				pthread_mutex_t *mutex);
t_coord			mutex_checker_coord(t_coord *var, pthread_mutex_t *mutex);

void			speaker_stereo(t_data *data);
t_coord			get_speaker_coord(t_map map, uint32_t occ);

#endif
