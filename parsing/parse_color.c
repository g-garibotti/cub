/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:19:29 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/03 14:16:22 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_valid_rgb(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

static int	check_duplicate_color(char type, t_map *map)
{
	if (type == 'F' && map->floor_color != -1)
		return (1);
	if (type == 'C' && map->ceil_color != -1)
		return (1);
	return (0);
}

static int	ft_str_is_numeric(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	parse_rgb_values(char *str, int *r, int *g, int *b)
{
	char	**split;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ',' && str[i + 1] == ',')
			return (0);
		i++;
	}
	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (ft_free_split(split), 0);
	if (!ft_str_is_numeric(split[0]) || !ft_str_is_numeric(split[1])
		|| !ft_str_is_numeric(split[2]))
		return (ft_free_split(split), 0);
	*r = ft_atoi(split[0]);
	*g = ft_atoi(split[1]);
	*b = ft_atoi(split[2]);
	ft_free_split(split);
	return (1);
}

int	parse_color(char *line, t_map *map)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(line, ' ');
	if (!split || !split[1] || split[2] || ft_strlen(split[0]) != 1)
		return (ft_free_split(split), 0);
	if (check_duplicate_color(split[0][0], map))
		return (ft_free_split(split), 0);
	if (!parse_rgb_values(split[1], &r, &g, &b) || !is_valid_rgb(r, g, b))
		return (ft_free_split(split), 0);
	if (split[0][0] == 'F')
		map->floor_color = (r << 16) | (g << 8) | b;
	else if (split[0][0] == 'C')
		map->ceil_color = (r << 16) | (g << 8) | b;
	else
	{
		ft_free_split(split);
		return (0);
	}
	ft_free_split(split);
	return (1);
}
