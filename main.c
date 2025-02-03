/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:15:08 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/03 13:39:54 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		clean_exit_msg("Usage: ./cub3D <map.cub>", NULL);
	init_game(&game);
	//PARSING
	parse_file(argv[1], &game);
	printf("BEFORE CLEAN END\n");
	// Continue with game initialization...
	clean_game(&game);
	return (0);
}
