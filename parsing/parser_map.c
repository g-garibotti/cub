/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:59:36 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/07 14:19:31 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_map_lines(t_game *game)
{
	char	*line;
	int		len;

	if (skip_to_map_start(game) < 0)
		clean_exit_msg("Invalid map start", game);
	game->map.height = 1;
	game->map.width = ft_strlen_no_nl(game->temp_map_line);
	line = get_next_line(game->fd);
	while (line)
	{
		if (is_empty_line(line))
		{
			free(line);
			clean_exit_msg("Invalid map: contains empty lines", game);
		}
		len = ft_strlen_no_nl(line);
		if (len > game->map.width)
			game->map.width = len;
		game->map.height++;
		free(line);
		line = get_next_line(game->fd);
	}
	if (game->map.height < 3 || game->map.width < 3)
		clean_exit_msg("Invalid map: too small", game);
}
