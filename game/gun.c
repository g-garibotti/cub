/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:42:48 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/07 12:55:04 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void draw_gun_sprite(t_game *game, t_texture *tex)
{
    int x, y, screen_x, screen_y;
    unsigned int color;
    double scale = 15.0;
    
    int scaled_width = tex->width * scale;
    int scaled_height = tex->height * scale;
    int pos_x = (S_W - scaled_width) / 2;
    int pos_y = S_H - scaled_height;
    
    y = 0;
    while (y < scaled_height)
    {
        x = 0;
        while (x < scaled_width)
        {
            screen_x = pos_x + x;
            screen_y = pos_y + y;
            
            if (screen_x >= 0 && screen_x < S_W && screen_y >= 0 && screen_y < S_H)
            {
                int tex_x = (int)(x / scale);
                int tex_y = (int)(y / scale);
                
                if (tex_x < tex->width && tex_y < tex->height)
                {
                    color = tex->addr[tex_y * tex->width + tex_x];
                    // Only draw non-transparent pixels (checking full 32-bit value)
                    if (color != 0)
                    {
                        game->addr[screen_y * S_W + screen_x] = color;
                    }
                }
            }
            x++;
        }
        y++;
    }
}

void update_gun_animation(t_game *game)
{
    if (game->gun.state == GUN_FIRING)
    {
        game->gun.anim_timer++;
        if (game->gun.anim_timer >= 3) // Adjust this value to control animation speed
        {
            game->gun.anim_timer = 0;
            game->gun.frame++;
            if (game->gun.frame >= GUN_FRAMES)
            {
                game->gun.frame = 0;
                game->gun.state = GUN_IDLE;
            }
        }
    }
}

void render_gun(t_game *game)
{
    if (game->gun.state == GUN_IDLE && game->gun.idle.img)
        draw_gun_sprite(game, &game->gun.idle);
    else if (game->gun.state == GUN_FIRING && game->gun.fire[game->gun.frame].img)
        draw_gun_sprite(game, &game->gun.fire[game->gun.frame]);
}
