/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:51:44 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/04 14:00:59 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	init_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (clean_exit_msg("Failed to initialize MLX", game));
	game->win = mlx_new_window(game->mlx, S_W, S_H, "cub3D");
	if (!game->win)
		return (clean_exit_msg("Failed to create window", game));
	game->img = mlx_new_image(game->mlx, S_W, S_H);
	if (!game->img)
		return (clean_exit_msg("Failed to create image", game));
	game->addr = (int *)mlx_get_data_addr(game->img, &game->bpp,
			&game->line_len, &game->endian);
	if (!game->addr)
		return (clean_exit_msg("Failed to get image address", game));
	return (0);
}

static int	init_rays(t_game *game)
{
	game->rays = malloc(sizeof(t_ray) * S_W);
	if (!game->rays)
		return (clean_exit_msg("Failed to allocate rays", game));
	return (0);
}

int	start_game(t_game *game)
{
	if (init_window(game) != 0)
		return (1);
	if (init_rays(game) != 0)
		return (1);
	if (load_textures(game) != 0)
		return (1);
	set_hooks(game);
	mlx_loop(game->mlx);
	return (0);
}
