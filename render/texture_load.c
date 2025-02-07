/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:01:04 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/07 12:55:19 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int load_single_texture(t_game *game, t_texture *texture)
{
    if (!texture || !texture->path)
        return (1);

    texture->img = mlx_xpm_file_to_image(game->mlx, texture->path,
            &texture->width, &texture->height);
    if (!texture->img)
        return (1);

    texture->addr = (int *)mlx_get_data_addr(texture->img, &texture->bpp,
            &texture->line_len, &texture->endian);
    if (!texture->addr)
    {
        mlx_destroy_image(game->mlx, texture->img);
        texture->img = NULL;
        return (1);
    }
    return (0);
}

int load_gun_textures(t_game *game)
{
    int i;
    
    // Load idle gun texture
    if (load_single_texture(game, &game->gun.idle))
        return (clean_exit_msg("Failed to load idle gun texture", game));
        
    // Load firing animation frames
    for (i = 0; i < GUN_FRAMES; i++)
    {
        if (load_single_texture(game, &game->gun.fire[i]))
            return (clean_exit_msg("Failed to load gun firing texture", game));
    }
    
    // Handle transparency for all gun textures
    for (i = 0; i < game->gun.idle.width * game->gun.idle.height; i++)
        if ((game->gun.idle.addr[i] & 0x00FFFFFF) == 0)
            game->gun.idle.addr[i] = 0;
            
    for (int j = 0; j < GUN_FRAMES; j++)
        for (i = 0; i < game->gun.fire[j].width * game->gun.fire[j].height; i++)
            if ((game->gun.fire[j].addr[i] & 0x00FFFFFF) == 0)
                game->gun.fire[j].addr[i] = 0;
    
    return (0);
}

int load_textures(t_game *game)
{
    if (load_single_texture(game, &game->map.north))
        return (clean_exit_msg("Failed to load north texture", game));
    if (load_single_texture(game, &game->map.south))
        return (clean_exit_msg("Failed to load south texture", game));
    if (load_single_texture(game, &game->map.east))
        return (clean_exit_msg("Failed to load east texture", game));
    if (load_single_texture(game, &game->map.west))
        return (clean_exit_msg("Failed to load west texture", game));
    if (game->map.door.path && load_single_texture(game, &game->map.door))
        return (clean_exit_msg("Failed to load door texture", game));
        
    // Load gun textures separately
    if (load_gun_textures(game))
        return (1);

    return (0);
}
