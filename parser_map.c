/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:59:36 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/03 12:40:14 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int parse_map_lines(t_game *game)
{
    char *line;
    int len;
    
    if (skip_to_map_start(game) < 0)
        return (clean_exit_msg("Invalid map start", game));
    game->map.height = 1;
    game->map.width = ft_strlen_no_nl(game->temp_map_line);
    while ((line = get_next_line(game->fd)))
    {
        if (is_empty_line(line))
        {
            free(line);  // Free current line
            return (clean_exit_msg("Invalid map: contains empty lines", game));
        }
        len = ft_strlen_no_nl(line);
        if (len > game->map.width)
            game->map.width = len;
        game->map.height++;
        free(line);  // Free line in each iteration
    } 
    if (game->map.height < 3 || game->map.width < 3)
        return (clean_exit_msg("Invalid map: too small", game));
    return (0);
}
