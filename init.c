/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:15:31 by ggaribot          #+#    #+#             */
/*   Updated: 2025/01/30 12:15:45 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static void init_map(t_map *map)
{
    map->grid = NULL;
    map->width = 0;
    map->height = 0;
    
    // Initialize texture structures
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
    
    // Initialize colors to -1 to indicate they haven't been set
    map->floor_color = -1;
    map->ceil_color = -1;
}

static void init_player(t_player *player)
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
}

void init_game(t_game *game)
{
    // Zero out everything first
    ft_memset(game, 0, sizeof(t_game));
    
    // Initialize specific components
    game->mlx = NULL;
    game->win = NULL;
    game->img = NULL;
    game->addr = NULL;
    game->rays = NULL;
    game->temp_map_line = NULL;
    
    // Initialize map structure
    init_map(&game->map);
    
    // Initialize player structure
    init_player(&game->player);
}
