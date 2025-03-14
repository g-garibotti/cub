/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:09:40 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/24 13:35:02 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
** Draws a vertical line for wall rendering
** Renders ceiling color from top of screen to wall start
** Applies texture to wall section
** Renders floor color from wall end to bottom of screen
*/
void	draw_vertical_line(t_game *game, int x, int start, int end)
{
	int	y;
	int	color;

	y = 0;
	color = game->map.ceil_color;
	while (y < start)
		game->addr[(y++) * S_W + x] = color;
	apply_texture(game, x, &game->rays[x]);
	y = end + 1;
	color = game->map.floor_color;
	while (y < S_H)
		game->addr[(y++) * S_W + x] = color;
}

/*
** Main ray casting loop that processes all screen columns
** For each column:
** - Casts a ray and calculates wall distances
** - Determines wall height and drawing bounds
** - Handles wall projection to create 3D effect
** - Calls draw_vertical_line to render the column
*/
void	cast_rays(t_game *game)
{
	int		x;
	t_ray	*ray;
	int		line_height;
	int		draw_start;
	int		draw_end;

	x = 0;
	while (x < S_W)
	{
		ray = &game->rays[x];
		cast_single_ray(game, ray, x);
		line_height = ray->wall_height;
		draw_start = -line_height / 2 + S_H / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + S_H / 2;
		if (draw_end >= S_H)
			draw_end = S_H - 1;
		draw_vertical_line(game, x, draw_start, draw_end);
		x++;
	}
}
