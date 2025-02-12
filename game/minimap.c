/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 16:17:01 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/12 13:59:56 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Draw one pixelwith coord and color
static void	draw_minimap_pixel(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < S_W && y >= 0 && y < S_H)
		game->addr[y * S_W + x] = color;
}

// draw one square of minimap with allneeded pixels
static void	draw_minimap_square(t_game *game, t_point pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			draw_minimap_pixel(game, pos.x + i, pos.y + j, color);
			j++;
		}
		i++;
	}
}

static void	draw_wall_if_valid(t_game *game, t_point draw_pos, int map_x,
		int map_y)
{
	if (map_x >= 0 && map_x < game->map.width && map_y >= 0
		&& map_y < game->map.height)
	{
		if (game->map.grid[map_y][map_x] == '1')
			draw_minimap_square(game, draw_pos, MINIMAP_TILE - 1, 0x888888);
	}
}

// draw every square of minimap grid
static void	draw_minimap_grid(t_game *game, t_point start, t_point map_start)
{
	int		x;
	int		y;
	t_point	draw_pos;

	y = 0;
	while (y < MINIMAP_VIEW)
	{
		x = 0;
		while (x < MINIMAP_VIEW)
		{
			draw_pos.x = start.x + x * MINIMAP_TILE;
			draw_pos.y = start.y + y * MINIMAP_TILE;
			draw_wall_if_valid(game, draw_pos, map_start.x + x, map_start.y
				+ y);
			x++;
		}
		y++;
	}
}

// first call fill all of black
// second draw walls
// third player in red n a more little square
void	render_minimap(t_game *game)
{
	t_point	start;
	t_point	map_start;
	t_point	player_center;
	double	rel_x;
	double	rel_y;

	start.x = MINIMAP_PADDING;
	start.y = MINIMAP_PADDING;
	map_start.x = (int)game->player.pos_x - MINIMAP_VIEW / 2;
	map_start.y = (int)game->player.pos_y - MINIMAP_VIEW / 2;
	draw_minimap_square(game, start, MINIMAP_SIZE, 0x222222);
	draw_minimap_grid(game, start, map_start);
	rel_x = game->player.pos_x - map_start.x;
	rel_y = game->player.pos_y - map_start.y;
	player_center.x = start.x + (rel_x * MINIMAP_TILE);
	player_center.y = start.y + (rel_y * MINIMAP_TILE);
	draw_minimap_square(game, (t_point){player_center.x - 2, player_center.y
		- 2}, 4, 0xFF0000);
}
