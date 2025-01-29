/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:28:04 by ggaribot          #+#    #+#             */
/*   Updated: 2025/01/29 14:17:24 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static int	check_required_elements(t_map *map)
{
	if (!map->north.path || !map->south.path || !map->west.path
		|| !map->east.path)
		return (0);
	if (map->floor_color == -1 || map->ceil_color == -1)
		return (0);
	return (1);
}

static int parse_scene_elements(int fd, t_game *game)
{
    char *line;
    int parsing_map = 0;

    game->temp_map_line = NULL;
    while ((line = get_next_line(fd)) && !parsing_map)
    {
        if (is_map_line(line))
        {
            if (!check_required_elements(&game->map))
                clean_exit_msg("Missing required elements", game);
            game->temp_map_line = line;  // Store in game structure
            parsing_map = 1;
            continue;
        }
        else  // Try to parse as texture or color
        {
            if (!parse_element(line, &game->map))
                clean_exit_msg("Invalid scene element", game);
            free(line);
        }
    }
    return (0);
}

static int parse_and_validate_map(int fd, t_game *game)
{
    t_list *map_lines = NULL;
    char *line;

    // Add the first map line to our list
    if (game->temp_map_line)
        ft_lstadd_back(&map_lines, ft_lstnew(ft_strdup(game->temp_map_line)));

    // Collect remaining map lines
    while ((line = get_next_line(fd)))
    {
        if (!is_empty_line(line))
            ft_lstadd_back(&map_lines, ft_lstnew(ft_strdup(line)));
        free(line);
    }

    // Validate map structure and content
    if (!validate_map_continuity(map_lines))
        clean_exit_msg("Invalid map: contains empty lines", game);
    if (!parse_map_content(map_lines, &game->map))
        clean_exit_msg("Invalid map structure", game);
    if (!validate_map(&game->map, &game->player))
        clean_exit_msg("Invalid map: player position error", game);

    ft_lstclear(&map_lines, free);
    return (0);
}

int parse_file(char *file, t_game *game)
{
    int fd;

    if (!check_file_extension(file))
        clean_exit_msg("Invalid file extension", game);
    fd = open(file, O_RDONLY);
    if (fd < 0)
        clean_exit_msg("Cannot open file", game);
    // Parse scene elements (textures and colors)
    parse_scene_elements(fd, game);
    // Parse and validate map
    parse_and_validate_map(fd, game);
    
    // Success cleanup
    free(game->temp_map_line);
    game->temp_map_line = NULL;
    close(fd);
    return (0);
}
