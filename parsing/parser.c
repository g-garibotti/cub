/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:28:04 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/21 14:39:50 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_required_elements(t_map *map)
{
	if (!map->north.path || !map->south.path || !map->west.path
		|| !map->east.path)
		return (0);
	if (map->floor_color == -1 || map->ceil_color == -1)
		return (0);
	return (1);
}

static int	process_scene_line(char *line, t_game *game)
{
	if (is_map_line(line))
	{
		if (!check_required_elements(&game->map))
			return (free(line), clean_exit_msg("Missing required elements",
					game));
		game->temp_map_line = ft_strdup(line);
		free(line);
		return (1);
	}
	if (!is_empty_line(line))
	{
		if (!parse_element(line, &game->map))
			return (free(line), clean_exit_msg("Invalid scene element", game));
	}
	free(line);
	return (0);
}

static int	parse_scene_elements(t_game *game)
{
	char	*line;
	int		ret;

	game->temp_map_line = NULL;
	line = get_next_line(game->fd);
	while (line)
	{
		ret = process_scene_line(line, game);
		if (ret == 1)
			break ;
		line = get_next_line(game->fd);
	}
	if (!game->temp_map_line)
		return (clean_exit_msg("No map found in file", game));
	return (0);
}

static void	validate_map(t_game *game)
{
	fill_map_array(game);
	map_validation(game);
}

void	parse_file(char *file, t_game *game)
{
	if (!file)
		clean_exit_msg("Invalid file path", game);
	if (!check_file_extension(file))
		clean_exit_msg("Invalid file extension", game);
	game->fd = open(file, O_RDONLY);
	if (game->fd < 0)
		clean_exit_msg("Cannot open file", game);
	parse_scene_elements(game);
	close(game->fd);
	game->fd = open(file, O_RDONLY);
	if (game->fd < 0)
		clean_exit_msg("Cannot open file", game);
	parse_map_lines(game);
	close(game->fd);
	game->fd = open(file, O_RDONLY);
	if (game->fd < 0)
		clean_exit_msg("Cannot open file", game);
	validate_map(game);
}
