/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:03:24 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/03 14:16:26 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	set_texture_path(char *identifier, char *path, t_map *map)
{
	if (ft_strcmp(identifier, "NO") == 0)
		map->north.path = ft_strdup(path);
	else if (ft_strcmp(identifier, "SO") == 0)
		map->south.path = ft_strdup(path);
	else if (ft_strcmp(identifier, "WE") == 0)
		map->west.path = ft_strdup(path);
	else if (ft_strcmp(identifier, "EA") == 0)
		map->east.path = ft_strdup(path);
	else
		return (0);
	return (1);
}

static int	check_duplicate_texture(char *identifier, t_map *map)
{
	if (ft_strcmp(identifier, "NO") == 0 && map->north.path != NULL)
		return (1);
	if (ft_strcmp(identifier, "SO") == 0 && map->south.path != NULL)
		return (1);
	if (ft_strcmp(identifier, "WE") == 0 && map->west.path != NULL)
		return (1);
	if (ft_strcmp(identifier, "EA") == 0 && map->east.path != NULL)
		return (1);
	return (0);
}

static int	check_texture_file(char *path)
{
	int		fd;
	char	*extension;

	if (!path)
		return (0);
	extension = ft_strrchr(path, '.');
	if (!extension || ft_strcmp(extension, ".xpm") != 0)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	parse_texture(char *line, t_map *map)
{
	char	**split;
	int		result;

	split = ft_split(line, ' ');
	if (!split)
		return (0);
	if (!split[1] || split[2])
	{
		ft_free_split(split);
		return (0);
	}
	if (check_duplicate_texture(split[0], map))
	{
		ft_free_split(split);
		return (0);
	}
	if (!check_texture_file(split[1]))
	{
		ft_free_split(split);
		return (0);
	}
	result = set_texture_path(split[0], split[1], map);
	ft_free_split(split);
	return (result);
}
