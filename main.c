/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:15:08 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/21 14:56:46 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	clean_exit_msg(char *msg, t_game *game)
{
	if (msg)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
		if (game)
			clean_game(game);
		exit(1);
	}
	if (game)
	{
		if (game->win && game->mlx)
			mlx_loop_end(game->mlx);
		clean_game(game);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	init_game(&game);
	parse_file(argv[1], &game);
	if (start_game(&game) != 0)
	{
		clean_game(&game);
		return (1);
	}
	clean_game(&game);
	printf("Game exited cleanly\n");
	return (0);
}
