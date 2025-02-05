/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:13:30 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/05 17:01:27 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_texture	*select_wall_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (game->player.pos_x > ray->map_x)
			return (&game->map.west);
		else
			return (&game->map.east);
	}
	else
	{
		if (game->player.pos_y > ray->map_y)
			return (&game->map.north);
		else
			return (&game->map.south);
	}
}

static void	get_draw_bounds(t_ray *ray, int *start, int *end)
{
	int	line_height;

	line_height = ray->wall_height;
	*start = -line_height / 2 + S_H / 2;
	if (*start < 0)
		*start = 0;
	*end = line_height / 2 + S_H / 2;
	if (*end >= S_H)
		*end = S_H - 1;
}

static int	get_texture_x(t_game *game, t_ray *ray, t_texture *tex)
{
	int	tex_x;

	tex_x = (int)(ray->wall_x * tex->width);
	if (ray->side == 0 && game->player.pos_x < ray->map_x)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && game->player.pos_y > ray->map_y)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}

static void	draw_textured_line(t_game *game, t_data *data)
{
	int	tex_y;

	while (data->y < data->draw_end)
	{
		tex_y = (int)((double)(data->y - (-data->ray->wall_height / 2 + S_H / 2))
				* data->tex->height / data->ray->wall_height);
		if (tex_y >= 0 && tex_y < data->tex->height && data->tex_x >= 0
			&& data->tex_x < data->tex->width)
			game->addr[data->y * S_W + data->x] = data->tex->addr[tex_y
				* data->tex->width + data->tex_x];
		data->y++;
	}
}

void	apply_texture(t_game *game, int x, t_ray *ray)
{
	t_texture	*tex;
	t_data		data;

	tex = select_wall_texture(game, ray);
	get_draw_bounds(ray, &data.draw_start, &data.draw_end);
	data.tex_x = get_texture_x(game, ray, tex);
	data.x = x;
	data.y = data.draw_start;
	data.tex = tex;
	data.ray = ray;
	draw_textured_line(game, &data);
}
