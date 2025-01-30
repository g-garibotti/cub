/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:47:01 by ggaribot          #+#    #+#             */
/*   Updated: 2025/01/30 12:34:10 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	check_file_extension(char *filename)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || ft_strcmp(dot, ".cub") != 0)
		return (0);
	return (1);
}

int is_map_line(char *line)
{
    // Skip leading whitespace
    while (*line && (*line == ' ' || *line == '\t'))
        line++;
        
    // Skip if empty line or just newline
    if (*line == '\0' || *line == '\n')
        return (0);
        
    // Check for valid map characters
    return (*line == '1' || *line == '0' || *line == ' ');
}

int is_empty_line(char *line)
{
    int i;

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
	// Find start
	start = str;
	while (*start && (*start == ' ' || *start == '\t'))
		start++;
	// Find end
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	// Calculate length and allocate
	len = (end - start) + 2;
	result = malloc(len);
	if (!result)
		return (NULL);
	// Copy and null terminate
	ft_strlcpy(result, start, len);
	return (result);
}
