/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:45:20 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/05 17:30:17 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**create_map_copy(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * game->map.height);
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < game->map.height)
	{
		map_copy[i] = ft_strdup(game->map.grid[i]);
		if (!map_copy[i])
		{
			free_map_copy(map_copy, i);
			return (NULL);
		}
		i++;
	}
	return (map_copy);
}

void	free_map_copy(char **map_copy, int height)
{
	int	i;

	if (!map_copy)
		return ;
	i = 0;
	while (i < height)
	{
		if (map_copy[i])
			free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

static int	is_valid_position(int x, int y, t_game *game)
{
	return (x >= 0 && x < game->map.width && y >= 0 && y < game->map.height);
}

static int can_flood(char c)
{
    return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'X');
}

void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (!is_valid_position(x, y, game) || map[y][x] == '1' || map[y][x] == 'V')
		return ;
	if (!can_flood(map[y][x]))
		return ;
	if (map[y][x] == 'X')
	{
		game->map.is_closed = 0;
		return ;
	}
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}
