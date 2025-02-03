/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:12:30 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/03 14:16:46 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_player_position(t_game *game, int x, int y)
{
	if (x <= 0 || x >= game->map.width - 1 || y <= 0 || y >= game->map.height
		- 1)
		return (0);
	if (game->map.grid[y][x + 1] == 'X' || game->map.grid[y][x - 1] == 'X'
		|| game->map.grid[y + 1][x] == 'X' || game->map.grid[y - 1][x] == 'X')
		return (0);
	return (1);
}

void	update_player_pos(t_game *game, int x, int y)
{
	game->player.pos_x = x;
	game->player.pos_y = y;
	game->player.orientation = game->map.grid[y][x];
	init_player_direction(&game->player);
}
