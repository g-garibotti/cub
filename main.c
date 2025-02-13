/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:15:08 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/13 11:57:52 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		clean_exit_msg("Usage: ./cub3D <map.cub>", NULL);
	init_game(&game);
	parse_file(argv[1], &game);
	if (start_game(&game) != 0)
	{
		printf("Error\nGame exited with an error\n");
		clean_game(&game);
		return (1);
	}
	printf("Game exited cleanly\n");
	return (0);
}
