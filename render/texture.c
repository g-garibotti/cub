/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:13:30 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/04 14:13:48 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	load_single_texture(t_game *game, t_texture *texture)
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

int	load_textures(t_game *game)
{
	if (load_single_texture(game, &game->map.north))
		return (clean_exit_msg("Failed to load north texture", game));
	if (load_single_texture(game, &game->map.south))
		return (clean_exit_msg("Failed to load south texture", game));
	if (load_single_texture(game, &game->map.east))
		return (clean_exit_msg("Failed to load east texture", game));
	if (load_single_texture(game, &game->map.west))
		return (clean_exit_msg("Failed to load west texture", game));
	return (0);
}

void	apply_texture(t_game *game, int x, t_ray *ray)
{
	t_texture	*tex;
	int			tex_x;
	int			tex_y;
	int			y;
	int			draw_start;
	int			draw_end;
	int			line_height;

	// Select texture based on which wall side was hit
	if (ray->side == 0)
		tex = (game->player.dir_x > 0) ? &game->map.west : &game->map.east;
	else
		tex = (game->player.dir_y > 0) ? &game->map.north : &game->map.south;
	// Calculate wall height
	line_height = ray->wall_height;
	draw_start = -line_height / 2 + S_H / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + S_H / 2;
	if (draw_end >= S_H)
		draw_end = S_H - 1;
	// Calculate texture X coordinate
	tex_x = (int)(ray->wall_x * tex->width);
	// Draw the textured vertical line
	y = draw_start;
	while (y < draw_end)
	{
		// Calculate texture Y coordinate
		tex_y = (int)((double)(y - (-line_height / 2 + S_H / 2)) * tex->height
				/ line_height);
		// Get color from texture and write to buffer
		if (tex_y >= 0 && tex_y < tex->height && tex_x >= 0
			&& tex_x < tex->width)
			game->addr[y * S_W + x] = tex->addr[tex_y * tex->width + tex_x];
		y++;
	}
}
