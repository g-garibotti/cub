/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:06:29 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/13 10:27:44 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/*
** Screen Constants
*/
# define S_W 1900
# define S_H 1000
# define TILE_SIZE 30
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 2
# define PI 3.14159265359
# define RAD 0.01745329251

/*
** Key Codes
*/
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SHIFT 65505
# define KEY_E 101

/*
** Minimap Settings
*/
# define MINIMAP_SIZE 200
# define MINIMAP_TILE 10
# define MINIMAP_VIEW 20
# define MINIMAP_PADDING 20

/*
** Gun States
*/
# define GUN_IDLE 0
# define GUN_FIRING 1
# define GUN_FRAMES 4

//Coordinates of a pixel, used in minimap and 2D calculs
typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

//Digital Differential Analysis
//Used to calculate the distance of the ray to the next wall
typedef struct s_dda
{
	double		ray_dir_x;
	double		ray_dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			hit;
	int			side;
}				t_dda;

//Player struct, pos/look vector/viewing angle/fov...
typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		angle;
	double		plane_x;
	double		plane_y;
	char		orientation;
	float		fov_rd;
	int			rot;
	int			l_r;
	int			u_d;
	int			sprint;
}				t_player;

//single ray cast from player
typedef struct s_ray
{
	double		ray_ngl;
	double		distance;
	double		wall_x;
	int			wall_height;
	int			side;
	int			map_x;
	int			map_y;
}				t_ray;

typedef struct s_texture
{
	void		*img;
	char		*path;
	int			*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_len;
	int			endian;
}				t_texture;

typedef struct s_data_gun
{
	double		scale;
	int			scaled_width;
	int			scaled_height;
	int			pos_x;
	int			pos_y;
	t_texture	*tex;
}				t_data_gun;

typedef struct s_gun
{
	t_texture	idle;
	t_texture	fire[GUN_FRAMES];
	int			state;
	int			frame;
	int			anim_timer;
}				t_gun;

typedef struct s_data
{
	int			draw_start;
	int			draw_end;
	int			tex_x;
	int			x;
	int			y;
	t_texture	*tex;
	t_ray		*ray;
}				t_data;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	t_texture	north;
	t_texture	south;
	t_texture	west;
	t_texture	east;
	int			floor_color;
	int			ceil_color;
	int			is_closed;
	t_texture	door;
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_player	player;
	t_map		map;
	t_ray		*rays;
	char		*temp_map_line;
	int			fd;
	t_gun		gun;
}				t_game;

/*
** Hook Functions
*/
int				handle_mouse(int x, int y, t_game *game);
int				game_loop(t_game *game);
int				handle_mouse_button(int button, int x, int y, t_game *game);
int				handle_window_close(t_game *game);
void			set_hooks(t_game *game);

/*
** Game Functions
*/
int				start_game(t_game *game);
void			init_game(t_game *game);
int				load_textures(t_game *game);
void			clean_game(t_game *game);
int				clean_exit_msg(char *msg, t_game *game);

/*
** Rendering Functions
*/
void			cast_rays(t_game *game);
void			render_walls(t_game *game);
void			render_minimap(t_game *game);
void			render_gun(t_game *game);
void			draw_vertical_line(t_game *game, int x, int start, int end);
void			cast_single_ray(t_game *game, t_ray *ray, int x);
void			apply_texture(t_game *game, int x, t_ray *ray);

/*
** Player Functions
*/
void			move_player(t_game *game);
void			rotate_player(t_game *game);
void			init_player_direction(t_player *player);
void			update_player_pos(t_game *game, int x, int y);
int				find_player(t_game *game);
int				check_collision(t_game *game, double new_x, double new_y);

/*
** Gun Functions
*/
int				load_gun_textures(t_game *game);
void			update_gun_animation(t_game *game);

/*
** Parser Functions
*/
void			parse_file(char *filename, t_game *game);
int				parse_texture(char *line, t_map *map);
int				parse_color(char *line, t_map *map);
int				parse_element(char *line, t_map *map);
void			parse_map_lines(t_game *game);
int				has_door_chars(t_game *game);
void			fill_map_array(t_game *game);
void			map_validation(t_game *game);

/*
** Utility Functions
*/
int				is_empty_line(char *line);
int				is_map_line(char *line);
char			*trim_whitespace(char *str);
int				check_file_extension(char *filename);
int				skip_to_map_start(t_game *game);
char			**create_map_copy(t_game *game);
void			flood_fill(char **map, int x, int y, t_game *game);
void			free_map_copy(char **map_copy, int height);
int				check_player_position(t_game *game, int x, int y);

/*
** Math Functions
*/
double			get_vector_length(double x, double y);
void			normalize_vector(double *x, double *y);
double			get_vector_angle(double x, double y);
void			get_perpendicular(double *x, double *y);

#endif