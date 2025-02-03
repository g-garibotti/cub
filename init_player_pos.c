/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:16:29 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/03 14:07:54 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void	set_north_direction(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
	player->angle = 270 * RAD;
}

static void	set_south_direction(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 1;
	player->plane_x = -0.66;
	player->plane_y = 0;
	player->angle = 90 * RAD;
}

static void	set_east_direction(t_player *player)
{
	player->dir_x = 1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	player->angle = 0;
}

static void	set_west_direction(t_player *player)
{
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = -0.66;
	player->angle = 180 * RAD;
}

void	init_player_direction(t_player *player)
{
	if (player->orientation == 'N')
		set_north_direction(player);
	else if (player->orientation == 'S')
		set_south_direction(player);
	else if (player->orientation == 'E')
		set_east_direction(player);
	else if (player->orientation == 'W')
		set_west_direction(player);
	player->fov_rd = FOV * RAD;
}
