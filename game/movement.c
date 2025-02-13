/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:03:59 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/13 11:16:27 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_collision(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(new_x);
	map_y = (int)(new_y);
	if (map_x < 0 || map_x >= game->map.width || map_y < 0
		|| map_y >= game->map.height)
		return (1);
	if (game->map.grid[map_y][map_x] == '1')
		return (1);
	if (game->map.grid[map_y][map_x] == 'd')
		return (1);
	if (game->map.grid[map_y][map_x] == 'X')
		return (1);
	return (0);
}

static void	handle_forward_movement(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	if (game->player.u_d != 0)
	{
		new_x = game->player.pos_x + game->player.dir_x * move_speed
			* game->player.u_d;
		new_y = game->player.pos_y + game->player.dir_y * move_speed
			* game->player.u_d;
		if (!check_collision(game, new_x, new_y))
		{
			game->player.pos_x = new_x;
			game->player.pos_y = new_y;
		}
	}
}

static void	handle_strafe_movement(t_game *game, double move_speed)
{
	double	new_x;
	double	new_y;

	if (game->player.l_r != 0)
	{
		new_x = game->player.pos_x + game->player.plane_x * move_speed
			* game->player.l_r;
		new_y = game->player.pos_y + game->player.plane_y * move_speed
			* game->player.l_r;
		if (!check_collision(game, new_x, new_y))
		{
			game->player.pos_x = new_x;
			game->player.pos_y = new_y;
		}
	}
}

void	move_player(t_game *game)
{
	double	move_speed;

	move_speed = PLAYER_SPEED * 0.05;
	if (game->player.sprint)
		move_speed *= 2.0;
	handle_forward_movement(game, move_speed);
	handle_strafe_movement(game, move_speed);
}

/*
** Handles player rotation
** Updates direction and camera plane vectors using rotation matrix
** Maintains angle between 0 and 2π
** Uses constant rotation speed defined by ROTATION_SPEED
*/
void	rotate_player(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	if (game->player.rot == 0)
		return ;
	rot_speed = ROTATION_SPEED * game->player.rot;
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y
		* cos(rot_speed);
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y
		* cos(rot_speed);
	game->player.angle += rot_speed;
	if (game->player.angle > 2 * PI)
		game->player.angle -= 2 * PI;
	else if (game->player.angle < 0)
		game->player.angle += 2 * PI;
}
