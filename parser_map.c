/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:59:36 by ggaribot          #+#    #+#             */
/*   Updated: 2025/01/30 11:50:12 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int parse_map_lines(int fd, t_game *game)
{
    char *line;
    int len;

    game->map.height = 1;  
    game->map.width = ft_strlen(game->temp_map_line);
    while ((line = get_next_line(fd)))
    {
        if (is_empty_line(line))
        {
            free(line);
            return (clean_exit_msg("Invalid map: contains empty lines", NULL));
        }
        len = ft_strlen(line);
        if (len > game->map.width)
            game->map.width = len;

        game->map.height++;
        free(line);
    }
    if (game->map.height < 3 || game->map.width < 3)
        return (clean_exit_msg("Invalid map: too small", NULL));

    return (0);
}
