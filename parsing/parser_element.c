/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_element.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:44:27 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/07 14:19:27 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	has_door_chars(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'D' || game->map.grid[y][x] == 'd')
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	parse_element(char *line, t_map *map)
{
	char	*trimmed;
	int		ret;

	if (is_empty_line(line))
		return (1);
	trimmed = trim_whitespace(line);
	if (!trimmed)
		return (0);
	ret = 0;
	if (trimmed[0] == 'N' || trimmed[0] == 'S' || trimmed[0] == 'W'
		|| trimmed[0] == 'E' || trimmed[0] == 'D')
		ret = parse_texture(trimmed, map);
	else if (trimmed[0] == 'F' || trimmed[0] == 'C')
		ret = parse_color(trimmed, map);
	else if (trimmed[0] == '1' || trimmed[0] == '0' || trimmed[0] == ' ')
		ret = 2;
	free(trimmed);
	return (ret);
}
