/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:47:01 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/07 14:19:37 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_file_extension(char *filename)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || ft_strcmp(dot, ".cub") != 0)
		return (0);
	return (1);
}

int	is_map_line(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (*line == '\0' || *line == '\n')
		return (0);
	return (*line == '1' || *line == '0' || *line == ' ');
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

char	*trim_whitespace(char *str)
{
	char	*start;
	char	*end;
	char	*result;
	int		len;

	if (!str)
		return (NULL);
	start = str;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	len = (end - start) + 2;
	result = malloc(len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, start, len);
	return (result);
}

int	skip_to_map_start(t_game *game)
{
	char	*line;
	int		map_start;

	map_start = 0;
	line = get_next_line(game->fd);
	while (line != NULL)
	{
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(game->fd);
			continue ;
		}
		if (is_map_line(line))
		{
			free(line);
			map_start = 1;
			break ;
		}
		free(line);
		line = get_next_line(game->fd);
	}
	if (!map_start)
		return (-1);
	return (0);
}
