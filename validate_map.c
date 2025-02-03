/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:44:44 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/03 11:18:26 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static int	check_player_position(t_game *game, int x, int y)
{
    // Check if player is at the edge of the map
    if (x <= 0 || x >= game->map.width - 1 || y <= 0 || y >= game->map.height - 1)
        return (0);

    // Check all adjacent cells are either walls or valid spaces
    if (game->map.grid[y][x + 1] == 'X' || game->map.grid[y][x - 1] == 'X' ||
        game->map.grid[y + 1][x] == 'X' || game->map.grid[y - 1][x] == 'X')
        return (0);

    return (1);
}

static void update_player_pos(t_game *game, int x, int y)
{
    game->player.pos_x = x;
    game->player.pos_y = y;
    game->player.orientation = game->map.grid[y][x];
    init_player_direction(&game->player);
}

static int find_player(t_game *game)
{
    int x;
    int y;
    int player_count;

    player_count = 0;
    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            if (ft_strchr("NSEW", game->map.grid[y][x]))
            {
                if (!check_player_position(game, x, y))
                    return (0);
                update_player_pos(game, x, y);
                player_count++;
            }
            x++;
        }
        y++;
    }
    return (player_count == 1);
}

static int	is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' ||
            c == 'E' || c == 'W' || c == 'X');
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

static int check_empty_spaces(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            if (game->map.grid[y][x] == '0')
            {
                // Check if empty space is adjacent to an 'X'
                if (x == 0 || x == game->map.width - 1 || 
                    y == 0 || y == game->map.height - 1)
                    return (0);
                if (game->map.grid[y][x + 1] == 'X' || 
                    game->map.grid[y][x - 1] == 'X' ||
                    game->map.grid[y + 1][x] == 'X' || 
                    game->map.grid[y - 1][x] == 'X')
                    return (0);
            }
            x++;
        }
        y++;
    }
    return (1);
}

int	map_validation(t_game *game)
{
    char	**map_copy;

    // Check for valid characters
    if (!check_map_chars(game))
        return (clean_exit_msg("Invalid character in map", game));

    // Check player position and count
    if (!find_player(game))
        return (clean_exit_msg("Invalid player position or count", game));

    // Check empty spaces
    if (!check_empty_spaces(game))
        return (clean_exit_msg("Map has exposed empty spaces", game));

    // Create map copy for flood fill
    map_copy = create_map_copy(game);
    if (!map_copy)
        return (clean_exit_msg("Memory allocation failed", game));

    // Initialize map as closed and perform flood fill
    game->map.is_closed = 1;
    flood_fill(map_copy, game->player.pos_x, game->player.pos_y, game);

    // Check if flood fill found any open edges
    if (!game->map.is_closed)
    {
        free_map_copy(map_copy, game->map.height);
        return (clean_exit_msg("Map is not properly closed", game));
    }

    free_map_copy(map_copy, game->map.height);
    return (0);
}
