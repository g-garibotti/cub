/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:52:16 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/12 14:04:25 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_door_interaction(t_game *game, double check_x, double check_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)check_x;
	map_y = (int)check_y;
	if (map_x < 0 || map_x >= game->map.width || map_y < 0
		|| map_y >= game->map.height)
		return (0);
	return (game->map.grid[map_y][map_x] == 'd'
		|| game->map.grid[map_y][map_x] == 'D');
}

static void	toggle_door(t_game *game)
{
	double	check_x;
	double	check_y;
	int		map_x;
	int		map_y;

	check_x = game->player.pos_x + game->player.dir_x * 1.0;
	check_y = game->player.pos_y + game->player.dir_y * 1.0;
	if (check_door_interaction(game, check_x, check_y))
	{
		map_x = (int)check_x;
		map_y = (int)check_y;
		if (game->map.grid[map_y][map_x] == 'd')
			game->map.grid[map_y][map_x] = 'D';
		else if (game->map.grid[map_y][map_x] == 'D')
			game->map.grid[map_y][map_x] = 'd';
	}
}

static int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_E)
		toggle_door(game);
	else if (keycode == KEY_ESC)
		return (clean_exit_msg(NULL, game));
	else if (keycode == KEY_W)
		game->player.u_d = 1;
	else if (keycode == KEY_S)
		game->player.u_d = -1;
	else if (keycode == KEY_A)
		game->player.l_r = -1;
	else if (keycode == KEY_D)
		game->player.l_r = 1;
	else if (keycode == KEY_LEFT)
		game->player.rot = -1;
	else if (keycode == KEY_RIGHT)
		game->player.rot = 1;
	else if (keycode == KEY_SHIFT)
		game->player.sprint = 1;
	return (0);
}

static int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_S)
		game->player.u_d = 0;
	else if (keycode == KEY_A || keycode == KEY_D)
		game->player.l_r = 0;
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		game->player.rot = 0;
	else if (keycode == KEY_SHIFT)
		game->player.sprint = 0;
	return (0);
}

void	set_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 6, 1L << 6, handle_mouse, game);
	mlx_hook(game->win, 4, 1L << 2, handle_mouse_button, game);
	mlx_hook(game->win, 17, 0, handle_window_close, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
