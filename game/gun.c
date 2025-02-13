/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:42:48 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/13 10:55:26 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// Print gun pixel one by one on screen only if its not transparent color
static void	draw_gun_pixel(t_game *game, t_data_gun *d, int x, int y)
{
	int				screen_x;
	int				screen_y;
	int				tex_x;
	int				tex_y;
	unsigned int	color;

	screen_x = d->pos_x + x;
	screen_y = d->pos_y + y;
	if (screen_x >= 0 && screen_x < S_W && screen_y >= 0 && screen_y < S_H)
	{
		tex_x = (int)(x / d->scale);
		tex_y = (int)(y / d->scale);
		if (tex_x < d->tex->width && tex_y < d->tex->height)
		{
			color = d->tex->addr[tex_y * d->tex->width + tex_x];
			if (color != 0)
				game->addr[screen_y * S_W + screen_x] = color;
		}
	}
}

// set data for gun especially scale and position
static void	init_gun_data(t_data_gun *d, t_texture *tex)
{
	d->scale = 15.0;
	d->scaled_width = tex->width * d->scale;
	d->scaled_height = tex->height * d->scale;
	d->pos_x = (S_W - d->scaled_width) / 2;
	d->pos_y = S_H - d->scaled_height;
	d->tex = tex;
}

static void	draw_gun_sprite(t_game *game, t_texture *tex)
{
	t_data_gun	d;
	int			x;
	int			y;

	init_gun_data(&d, tex);
	y = 0;
	while (y < d.scaled_height)
	{
		x = 0;
		while (x < d.scaled_width)
		{
			draw_gun_pixel(game, &d, x, y);
			x++;
		}
		y++;
	}
}

// make the gun fire
void	update_gun_animation(t_game *game)
{
	if (game->gun.state == GUN_FIRING)
	{
		game->gun.anim_timer++;
		if (game->gun.anim_timer >= 3)
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

void	render_gun(t_game *game)
{
	if (game->gun.state == GUN_IDLE && game->gun.idle.img)
		draw_gun_sprite(game, &game->gun.idle);
	else if (game->gun.state == GUN_FIRING
		&& game->gun.fire[game->gun.frame].img)
		draw_gun_sprite(game, &game->gun.fire[game->gun.frame]);
}
