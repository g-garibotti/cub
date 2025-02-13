/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 14:04:41 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/13 11:30:35 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//delta x detrmine rotation and speed
//track mouse position change and rotate player
int	handle_mouse(int x, int y, t_game *game)
{
	static int	last_x = -1;
	int			delta_x;

	(void)y;
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	delta_x = x - last_x;
	if (delta_x != 0)
	{
		game->player.angle += delta_x * 0.003;
		game->player.dir_x = cos(game->player.angle);
		game->player.dir_y = sin(game->player.angle);
		game->player.plane_x = -game->player.dir_y * 0.66;
		game->player.plane_y = game->player.dir_x * 0.66;
	}
	last_x = x;
	return (0);
}

int	game_loop(t_game *game)
{
	move_player(game);
	rotate_player(game);
	ft_memset(game->addr, 0, S_W * S_H * sizeof(int));
	cast_rays(game);
	cast_rays(game);
	render_minimap(game);
	update_gun_animation(game);
	render_gun(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	handle_mouse_button(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1 && game->gun.state == GUN_IDLE)
	{
		game->gun.state = GUN_FIRING;
		game->gun.frame = 0;
		game->gun.anim_timer = 0;
	}
	return (0);
}

int	handle_window_close(t_game *game)
{
	return (clean_exit_msg(NULL, game));
}
