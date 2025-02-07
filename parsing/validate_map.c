/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:44:44 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/07 14:20:17 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'X' || c == 'd' || c == 'D');
}

static int	check_map_chars(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (!is_valid_char(game->map.grid[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	check_surrounding(t_game *game, int x, int y)
{
	if (x == 0 || x == game->map.width - 1 || y == 0 || y == game->map.height
		- 1)
		return (0);
	if (game->map.grid[y][x + 1] == 'X' || game->map.grid[y][x - 1] == 'X'
		|| game->map.grid[y + 1][x] == 'X' || game->map.grid[y - 1][x] == 'X'
		|| game->map.grid[y - 1][x - 1] == 'X' || game->map.grid[y - 1][x
		+ 1] == 'X' || game->map.grid[y + 1][x - 1] == 'X' || game->map.grid[y
		+ 1][x + 1] == 'X')
		return (0);
	return (1);
}

static int	check_empty_spaces(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == '0' && !check_surrounding(game, x, y))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	map_validation(t_game *game)
{
	char	**map_copy;

	if (!check_map_chars(game))
		clean_exit_msg("Invalid character in map", game);
	if (has_door_chars(game) && !game->map.door.path)
		clean_exit_msg("Door in map but no door texture specified", game);
	if (!find_player(game))
		clean_exit_msg("Invalid player position or count", game);
	if (!check_empty_spaces(game))
		clean_exit_msg("Map has exposed empty spaces", game);
	map_copy = create_map_copy(game);
	if (!map_copy)
		clean_exit_msg("Memory allocation failed", game);
	game->map.is_closed = 1;
	flood_fill(map_copy, game->player.pos_x, game->player.pos_y, game);
	if (!game->map.is_closed)
	{
		free_map_copy(map_copy, game->map.height);
		clean_exit_msg("Map is not properly closed", game);
	}
	free_map_copy(map_copy, game->map.height);
}
