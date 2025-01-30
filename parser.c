/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:28:04 by ggaribot          #+#    #+#             */
/*   Updated: 2025/01/30 13:35:58 by ggaribot         ###   ########.fr       */
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
    printf("\n--- Starting Scene Elements Parsing ---\n");
    while ((line = get_next_line(fd)) && !parsing_map)
    {
        if (is_map_line(line))
        {
            printf("\nChecking required elements before map parsing:\n");
            printf("North texture: %s\n", game->map.north.path);
            printf("South texture: %s\n", game->map.south.path);
            printf("West texture: %s\n", game->map.west.path);
            printf("East texture: %s\n", game->map.east.path);
            printf("Floor color: %d\n", game->map.floor_color);
            printf("Ceiling color: %d\n", game->map.ceil_color);
            
            if (!check_required_elements(&game->map))
            {
                free(line);
                return (clean_exit_msg("Missing required elements", game));
            }
            game->temp_map_line = line;
            parsing_map = 1;
            continue;
        }
        if (!is_empty_line(line))
        {
            printf("Parsing line: '%s'\n", line);
            if (!parse_element(line, &game->map))
            {
                free(line);
                return (clean_exit_msg("Invalid scene element", game));
            }
        }
        free(line);
    }
    return (0);
}

static int parse_and_validate_map(int fd, t_game *game)
{
    // Get map dimensions and check for empty lines
    if (parse_map_lines(fd, game))
        return (1);
    
    // At this point game->map.width and game->map.height are set
    printf("Map dimensions: %d x %d\n", game->map.width, game->map.height); // Debug line
    
    return (0);
}

/*
static int parse_and_validate_map(int fd, t_game *game)
{
    t_list *map_lines = NULL;

    ft_lstadd_back(&map_lines, ft_lstnew(ft_strdup(game->temp_map_line)));
    parse_map_lines(fd, &map_lines);


    // Validate map structure and player position
    if (!parse_map_content(map_lines, &game->map))
    {
        ft_lstclear(&map_lines, free);
        return (clean_exit_msg("Invalid map structure", game));
    }
    if (!validate_map(&game->map, &game->player))
    {
        ft_lstclear(&map_lines, free);
        return (clean_exit_msg("Invalid map: player position error", game));
    }

    ft_lstclear(&map_lines, free);
    return (0);
}*/

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
    close(fd);
    fd = open(file, O_RDONLY);
    // Parse and validate map
    parse_and_validate_map(fd, game);
    
    // Success cleanup
    free(game->temp_map_line);
    game->temp_map_line = NULL;
    close(fd);
    return (0);
}
