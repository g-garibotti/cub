/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:06:30 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/24 13:35:06 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Delta distances represent distance between X or Y intersections
static void	init_dda_values(t_dda *dda, t_game *game, double camera_x)
{
	dda->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	dda->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	dda->map_x = (int)game->player.pos_x;
	dda->map_y = (int)game->player.pos_y;
	dda->delta_dist_x = fabs(1 / dda->ray_dir_x);
	dda->delta_dist_y = fabs(1 / dda->ray_dir_y);
	dda->hit = 0;
}

/*
** Calculates initial step direction and side distances for DDA
** Determines which direction to step in X and Y
** Computes distance to first X and Y intersections with grid
** Step values are either 1 or -1 depending on ray direction
*/
static void	calculate_step_and_side_dist(t_dda *dda, t_game *game)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (game->player.pos_x - dda->map_x)
			* dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - game->player.pos_x)
			* dda->delta_dist_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (game->player.pos_y - dda->map_y)
			* dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - game->player.pos_y)
			* dda->delta_dist_y;
	}
}

/*
** Executes the DDA algorithm to find wall intersection
** Steps through the map grid until a wall is hit
** Keeps track of which side (X or Y) of wall was hit
** Updates map coordinates as it moves through grid
*/
static void	perform_dda(t_dda *dda, t_game *game)
{
	while (dda->hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (game->map.grid[dda->map_y][dda->map_x] == '1'
			|| game->map.grid[dda->map_y][dda->map_x] == 'd')
			dda->hit = 1;
	}
}

void	cast_single_ray(t_game *game, t_ray *ray, int x)
{
	t_dda	dda;
	double	camera_x;
	double	perp_wall_dist;

	camera_x = 2 * x / (double)S_W - 1;
	init_dda_values(&dda, game, camera_x);
	calculate_step_and_side_dist(&dda, game);
	perform_dda(&dda, game);
	if (dda.side == 0)
		perp_wall_dist = (dda.map_x - game->player.pos_x + (1 - dda.step_x) / 2)
			/ dda.ray_dir_x;
	else
		perp_wall_dist = (dda.map_y - game->player.pos_y + (1 - dda.step_y) / 2)
			/ dda.ray_dir_y;
	ray->distance = perp_wall_dist;
	ray->side = dda.side;
	ray->map_x = dda.map_x;
	ray->map_y = dda.map_y;
	if (dda.side == 0)
		ray->wall_x = game->player.pos_y + perp_wall_dist * dda.ray_dir_y;
	else
		ray->wall_x = game->player.pos_x + perp_wall_dist * dda.ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->wall_height = (int)(S_H / perp_wall_dist);
}
