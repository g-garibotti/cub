/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:19:29 by ggaribot          #+#    #+#             */
/*   Updated: 2025/01/29 15:12:39 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

static int	is_valid_rgb(int r, int g, int b)
{
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

static int check_duplicate_color(char type, t_map *map)
{
    if (type == 'F' && map->floor_color != -1)
        return (1);
    if (type == 'C' && map->ceil_color != -1)
        return (1);
    return (0);
}

static int check_trailing_chars_and_commas(char *str)
{
    int i;
    int comma_count;

    i = 0;
    comma_count = 0;
    while (str[i])
    {
        if (str[i] == ',')
        {
            comma_count++;
            if (str[i + 1] == ',')
                return (0);
        }
        i++;
    }
    i--;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
        i--;
    if (i < 0 || !ft_isdigit(str[i]))
        return (0);
    return (comma_count == 2);
}

static int parse_rgb_values(char *str, int *r, int *g, int *b)
{
    char **split;
    char *temp;
    int valid;

    split = ft_split(str, ',');
    if (!split || !split[0] || !split[1] || !split[2] || split[3])
        return (ft_free_split(split), 0);
    valid = 1;
    *r = ft_atoi(split[0]);
    temp = ft_itoa(*r);
    if (!temp || ft_strcmp(temp, split[0]) != 0)
        valid = 0;
    free(temp);
    *g = ft_atoi(split[1]);
    temp = ft_itoa(*g);
    if (valid && (!temp || ft_strcmp(temp, split[1]) != 0))
        valid = 0;
    free(temp);
    *b = ft_atoi(split[2]);
    temp = ft_itoa(*b);
    if (valid && (!temp || ft_strcmp(temp, split[2]) != 0))
        valid = 0;
    free(temp);
    ft_free_split(split);
    return (valid);
}

int parse_color(char *line, t_map *map)
{
    char    **split;
    int     r;
    int     g;
    int     b;

    split = ft_split(line, ' ');
    if (!split || !split[1] || ft_strlen(split[0]) != 1)
        return (ft_free_split(split), 0);
    if (check_duplicate_color(split[0][0], map))
        return (ft_free_split(split), 0);
    if (!check_trailing_chars_and_commas(split[1]))
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
