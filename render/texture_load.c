/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:01:04 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/12 13:52:33 by ggaribot         ###   ########.fr       */
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

static void	set_transparent_pixels(t_texture *texture)
{
	int	i;
	int	size;

	i = 0;
	size = texture->width * texture->height;
	while (i < size)
	{
		if ((texture->addr[i] & 0x00FFFFFF) == 0)
			texture->addr[i] = 0;
		i++;
	}
}

static int	load_firing_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < GUN_FRAMES)
	{
		if (load_single_texture(game, &game->gun.fire[i]))
			return (clean_exit_msg("Failed to load gun firing texture", game));
		set_transparent_pixels(&game->gun.fire[i]);
		i++;
	}
	return (0);
}

int	load_gun_textures(t_game *game)
{
	if (load_single_texture(game, &game->gun.idle))
		return (clean_exit_msg("Failed to load idle gun texture", game));
	set_transparent_pixels(&game->gun.idle);
	if (load_firing_textures(game))
		return (1);
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
	if (game->map.door.path && load_single_texture(game, &game->map.door))
		return (clean_exit_msg("Failed to load door texture", game));
	if (load_gun_textures(game))
		return (1);
	return (0);
}
