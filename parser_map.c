/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:59:36 by ggaribot          #+#    #+#             */
/*   Updated: 2025/01/30 12:34:31 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int parse_map_lines(int fd, t_game *game)
{
    char *line;
    int len;
    
    printf("\n--- Starting Map Parsing ---\n");
    game->map.height = 1;
    game->map.width = ft_strlen_no_nl(game->temp_map_line);
    printf("Initial map line (%d chars): '%s'", game->map.width, game->temp_map_line);
    
    while ((line = get_next_line(fd)))
    {
        if (is_empty_line(line))
        {
            free(line);
            return (clean_exit_msg("Invalid map: contains empty lines", NULL));
        }
        
        len = ft_strlen_no_nl(line);
        if (len > game->map.width)
            game->map.width = len;

        game->map.height++;
        printf("Map line %d (%d chars): '%s'", game->map.height, len, line);
        free(line);
    }
    
    printf("\nFinal map dimensions: %d x %d\n", game->map.width, game->map.height);
    
    if (game->map.height < 3 || game->map.width < 3)
        return (clean_exit_msg("Invalid map: too small", NULL));

    return (0);
}
