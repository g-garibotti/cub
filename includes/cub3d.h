#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* Constants */
# define S_W 1900             // screen width
# define S_H 1000             // screen height
# define TILE_SIZE 30         // tile size
# define FOV 60               // field of view
# define ROTATION_SPEED 0.045 // rotation speed
# define PLAYER_SPEED 2       // player speed
# define PI 3.14159265359
# define RAD (PI / 180)

/* Additional Key Codes */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SHIFT 65505 
#define KEY_E 101

/* Minimap */
# define MINIMAP_SIZE 200     // size of minimap
# define MINIMAP_TILE 10      // size of tile in minimap
# define MINIMAP_VIEW 20      // number of tiles visible in minimap
# define MINIMAP_PADDING 20   // padding from screen edge

/* Structures */

typedef struct s_point
{
	int	x;
	int	y;
}			t_point;

typedef struct s_dda
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		hit;
	int		side;
}			t_dda;

typedef struct s_player
{
	double pos_x;     // player x position
	double pos_y;     // player y position
	double dir_x;     // direction vector x
	double dir_y;     // direction vector y
	double angle;     // player angle
	double plane_x;   // camera plane x
	double plane_y;   // camera plane y
	char orientation; // initial orientation (N,S,E,W)
	float fov_rd;     // field of view in radians
	int rot;          // rotation flag
	int l_r;          // left/right movement flag
	int u_d;          // up/down movement flag
	int sprint;       // sprint flag
}			t_player;

typedef struct s_ray
{
    double ray_ngl;   // ray angle
    double distance;  // distance to wall
    double wall_x;    // wall hit position for texturing
    int wall_height;  // height of wall to render
    int side;         // which side of wall was hit (0 for x, 1 for y)
    int map_x;        // x coordinate of map cell hit
    int map_y;        // y coordinate of map cell hit
}           t_ray;

typedef struct s_texture
{
	void *img;    // texture image pointer
	char *path;   // path to texture file
	int *addr;    // texture data address
	int width;    // texture width
	int height;   // texture height
	int bpp;      // bits per pixel
	int line_len; // line length
	int endian;   // endianness
}			t_texture;

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
	char **grid;     // 2D map array
	int width;       // map width
	int height;      // map height
	t_texture north; // north wall texture
	t_texture south; // south wall texture
	t_texture west;  // west wall texture
	t_texture east;  // east wall texture
	int floor_color; // floor color (RGB)
	int ceil_color;  // ceiling color (RGB)
	int is_closed;   // flag to check if map is closed
	t_texture door;  // door texture
}			t_map;

typedef struct s_game
{
	void *mlx;           // MLX pointer
	void *win;           // window pointer
	void *img;           // main image pointer
	int *addr;           // image data address
	int bpp;             // bits per pixel
	int line_len;        // line length
	int endian;          // endianness
	t_player player;     // player data
	t_map map;           // map data
	t_ray *rays;         // array of rays
	char *temp_map_line; // temporary storage for map parsing
	int fd;              // file descriptor
}			t_game;

/* Function Prototypes */

// Minimap functions
void	render_minimap(t_game *game);

// Core game functions
int			start_game(t_game *game);
void		set_hooks(t_game *game);
void		init_game(t_game *game);

// Parsing functions
void		parse_file(char *filename, t_game *game);
int			parse_texture(char *line, t_map *map);
int			parse_color(char *line, t_map *map);
int			parse_element(char *line, t_map *map);
void		parse_map_lines(t_game *game);

// Parser utilities
int			is_empty_line(char *line);
int			is_map_line(char *line);
char		*trim_whitespace(char *str);
int			check_file_extension(char *filename);
int			skip_to_map_start(t_game *game);
void		fill_map_array(t_game *game);

// Map validation
void		map_validation(t_game *game);
char		**create_map_copy(t_game *game);
void		flood_fill(char **map, int x, int y, t_game *game);
void		free_map_copy(char **map_copy, int height);
int			check_player_position(t_game *game, int x, int y);

// Player functions
void		init_player_direction(t_player *player);
void		update_player_pos(t_game *game, int x, int y);
int			find_player(t_game *game);
void		move_player(t_game *game);
void		rotate_player(t_game *game);
int			check_collision(t_game *game, double new_x, double new_y);

// Math functions
double		get_vector_length(double x, double y);
void		normalize_vector(double *x, double *y);
double		get_vector_angle(double x, double y);
void		get_perpendicular(double *x, double *y);
void		cast_single_ray(t_game *game, t_ray *ray, int x);

// Rendering functions
void		cast_rays(t_game *game);
void		render_walls(t_game *game);
void		draw_vertical_line(t_game *game, int x, int start, int end);

// Texture functions
int			load_textures(t_game *game);
void		apply_texture(t_game *game, int x, t_ray *ray);

// Cleanup functions
void		clean_game(t_game *game);
int			clean_exit_msg(char *msg, t_game *game);

#endif