/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:14:27 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/21 18:08:39 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void	clean_texture(void *mlx, t_texture *texture)
{
	if (!texture)
		return ;
	if (texture->path)
	{
		free(texture->path);
	}
	if (texture->img && mlx)
	{
		mlx_destroy_image(mlx, texture->img);
		texture->img = NULL;
	}
}

static void	clean_map(void *mlx, t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->height && map->grid[i])
		{
			free(map->grid[i]);
			map->grid[i] = NULL;
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
	clean_texture(mlx, &map->north);
	clean_texture(mlx, &map->south);
	clean_texture(mlx, &map->east);
	clean_texture(mlx, &map->west);
	clean_texture(mlx, &map->door);
}

static void	clean_gun(t_game *game)
{
	int	i;

	if (!game)
		return ;
	clean_texture(game->mlx, &game->gun.idle);
	i = 0;
	while (i < GUN_FRAMES)
	{
		clean_texture(game->mlx, &game->gun.fire[i]);
		i++;
	}
}

void	clean_game(t_game *game)
{
	clean_map(game->mlx, &game->map);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	clean_gun(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (game->fd != -1)
	{
		close(game->fd);
		game->fd = -1;
	}
	if (game->rays)
		free(game->rays);
	if (game->temp_map_line)
		free(game->temp_map_line);
	game->bpp = 0;
	game->line_len = 0;
	game->endian = 0;
}

int	clean_exit_msg(char *msg, t_game *game)
{
	if (msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
		if (game)
			clean_game(game);
		exit(1);
	}
	if (game)
		clean_game(game);
	return (1);
}
