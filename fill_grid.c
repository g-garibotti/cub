/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:56:45 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/03 12:39:45 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static int allocate_map_grid(t_game *game)
{
    int i;
    int j;
    
    game->map.grid = malloc(sizeof(char *) * game->map.height);
    if (!game->map.grid)
        return (1);
    
    i = 0;
    while (i < game->map.height)
    {
        game->map.grid[i] = malloc(sizeof(char) * (game->map.width + 1));
        if (!game->map.grid[i])
            return (1);
            
        j = 0;
        while (j < game->map.width)
        {
            game->map.grid[i][j] = 'X';
            j++;
        }
        game->map.grid[i][game->map.width] = '\0';
        i++;
    }
    return (0);
}

static void fill_line(char *grid_line, char *source_line, int width)
{
    int j;
    
    j = 0;
    while (source_line[j] && source_line[j] != '\n' && j < width)
    {
        if (source_line[j] == ' ')
            grid_line[j] = 'X';
        else
            grid_line[j] = source_line[j];
        j++;
    }
}

static int fill_first_line(t_game *game)
{
    if (!game->temp_map_line)
        return (1);
    fill_line(game->map.grid[0], game->temp_map_line, game->map.width);
    return (0);
}

static int fill_remaining_lines(t_game *game)
{
    char *line;
    int i;
    
    i = 1;  // Start from second line
    while ((line = get_next_line(game->fd)) && i < game->map.height)
    {
        fill_line(game->map.grid[i], line, game->map.width);
        free(line);
        i++;
    }
    return (0);
}

static void debug_print_map(t_game *game)
{
    int i;
    
    printf("\nFilled map array:\n");
    i = 0;
    while (i < game->map.height)
    {
        printf("%s\n", game->map.grid[i]);
        i++;
    }
}

int fill_map_array(t_game *game)
{
    if (skip_to_map_start(game) < 0)
        clean_exit_msg("Invalid map start", game);
    if (allocate_map_grid(game) != 0)
        clean_exit_msg("Failed to allocate memory for map grid", game);
    if (fill_first_line(game) != 0)
        clean_exit_msg("Failed to fill first line of map", game); 
    if (fill_remaining_lines(game) != 0)
        clean_exit_msg("Failed to fill remaining lines of map", game);
    debug_print_map(game);
    close(game->fd);
    return (0);
}
