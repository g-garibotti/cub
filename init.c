/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:15:31 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/21 14:50:29 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void	init_gun(t_gun *gun)
{
	int		i;
	char	*number;
	char	*temp;

	gun->idle.path = ft_strdup("./textures/gun_idle.xpm");
	gun->idle.img = NULL;
	gun->idle.addr = NULL;
	i = 0;
	while (i < GUN_FRAMES)
	{
		number = ft_itoa(i + 1);
		temp = ft_strjoin("./textures/gun_fire_", number);
		free(number);
		gun->fire[i].path = ft_strjoin_free(temp, ".xpm");
		gun->fire[i].img = NULL;
		gun->fire[i].addr = NULL;
		i++;
	}
	gun->state = GUN_IDLE;
	gun->frame = 0;
	gun->anim_timer = 0;
}

static void	init_map(t_map *map)
{
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->is_closed = 0;
	map->north.img = NULL;
	map->north.path = NULL;
	map->north.addr = NULL;
	map->south.img = NULL;
	map->south.path = NULL;
	map->south.addr = NULL;
	map->east.img = NULL;
	map->east.path = NULL;
	map->east.addr = NULL;
	map->west.img = NULL;
	map->west.path = NULL;
	map->west.addr = NULL;
	map->floor_color = -1;
	map->ceil_color = -1;
	map->door.img = NULL;
	map->door.path = NULL;
	map->door.addr = NULL;
}

static void	init_player(t_player *player)
{
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->angle = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->orientation = 0;
	player->fov_rd = 0;
	player->rot = 0;
	player->l_r = 0;
	player->u_d = 0;
	player->sprint = 0;
}

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->addr = NULL;
	game->rays = NULL;
	game->temp_map_line = NULL;
	game->fd = -1;
	init_map(&game->map);
	init_player(&game->player);
	init_gun(&game->gun);
}
