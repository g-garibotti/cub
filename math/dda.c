/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:06:30 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/05 16:55:42 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_dda_values(t_dda *dda, t_game *game, double camera_x)
{
	// Calculate ray position and direction
	dda->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	dda->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	// Current map position
	dda->map_x = (int)game->player.pos_x;
	dda->map_y = (int)game->player.pos_y;
	// Length of ray from one side to next
	dda->delta_dist_x = fabs(1 / dda->ray_dir_x);
	dda->delta_dist_y = fabs(1 / dda->ray_dir_y);
	dda->hit = 0;
}

static void	calculate_step_and_side_dist(t_dda *dda, t_game *game)
{
	// Calculate step and initial side distance
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

static void	perform_dda(t_dda *dda, t_game *game)
{
	// DDA algorithm
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
		if (game->map.grid[dda->map_y][dda->map_x] == '1')
			dda->hit = 1;
	}
}

void    cast_single_ray(t_game *game, t_ray *ray, int x)
{
    t_dda   dda;
    double  camera_x;
    double  perp_wall_dist;

    // Calculate camera x-coordinate in camera space
    camera_x = 2 * x / (double)S_W - 1;
    init_dda_values(&dda, game, camera_x);
    calculate_step_and_side_dist(&dda, game);
    perform_dda(&dda, game);
    
    // Calculate distance to wall
    if (dda.side == 0)
        perp_wall_dist = (dda.map_x - game->player.pos_x + (1 - dda.step_x) / 2)
            / dda.ray_dir_x;
    else
        perp_wall_dist = (dda.map_y - game->player.pos_y + (1 - dda.step_y) / 2)
            / dda.ray_dir_y;
    
    // Store ray information
    ray->distance = perp_wall_dist;
    ray->side = dda.side;
    ray->map_x = dda.map_x;
    ray->map_y = dda.map_y;
    
    // Calculate wall X for texturing
    if (dda.side == 0)
        ray->wall_x = game->player.pos_y + perp_wall_dist * dda.ray_dir_y;
    else
        ray->wall_x = game->player.pos_x + perp_wall_dist * dda.ray_dir_x;
    ray->wall_x -= floor(ray->wall_x);
    
    // Calculate wall height
    ray->wall_height = (int)(S_H / perp_wall_dist);
}
