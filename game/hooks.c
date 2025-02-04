/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:52:16 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/04 14:00:47 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		return (clean_exit_msg(NULL, game));
	else if (keycode == XK_w || keycode == XK_W)
		game->player.u_d = 1;
	else if (keycode == XK_s || keycode == XK_S)
		game->player.u_d = -1;
	else if (keycode == XK_a || keycode == XK_A)
		game->player.l_r = -1;
	else if (keycode == XK_d || keycode == XK_D)
		game->player.l_r = 1;
	else if (keycode == XK_Left)
		game->player.rot = -1;
	else if (keycode == XK_Right)
		game->player.rot = 1;
	return (0);
}

static int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_w || keycode == XK_W)
		game->player.u_d = 0;
	else if (keycode == XK_s || keycode == XK_S)
		game->player.u_d = 0;
	else if (keycode == XK_a || keycode == XK_A)
		game->player.l_r = 0;
	else if (keycode == XK_d || keycode == XK_D)
		game->player.l_r = 0;
	else if (keycode == XK_Left)
		game->player.rot = 0;
	else if (keycode == XK_Right)
		game->player.rot = 0;
	return (0);
}

static int	game_loop(t_game *game)
{
	// Update player position and rotation
	move_player(game);
	rotate_player(game);
	// Clear the screen (fill with black)
	ft_memset(game->addr, 0, S_W * S_H * sizeof(int));
	// Cast rays and render the scene
	cast_rays(game);
	render_walls(game);
	// Put the image to window
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

static int	close_window(t_game *game)
{
	return (clean_exit_msg(NULL, game));
}

void	set_hooks(t_game *game)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, close_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
