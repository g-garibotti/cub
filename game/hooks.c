/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggaribot <ggaribot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:52:16 by ggaribot          #+#    #+#             */
/*   Updated: 2025/02/05 17:32:24 by ggaribot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_E)  // Add KEY_E to your defines (usually 101)
    {
        // Check if player is facing a door
        double check_x = game->player.pos_x + game->player.dir_x;
        double check_y = game->player.pos_y + game->player.dir_y;
        
        int map_x = (int)check_x;
        int map_y = (int)check_y;
        
        // If we're looking at a door, toggle it
        if (map_x >= 0 && map_x < game->map.width && 
            map_y >= 0 && map_y < game->map.height)
        {
            if (game->map.grid[map_y][map_x] == 'd')
                game->map.grid[map_y][map_x] = 'D';
            else if (game->map.grid[map_y][map_x] == 'D')
                game->map.grid[map_y][map_x] = 'd';
        }
    }
    else if (keycode == KEY_ESC)
        return (clean_exit_msg(NULL, game));
    else if (keycode == KEY_W)
        game->player.u_d = 1;
    else if (keycode == KEY_S)
        game->player.u_d = -1;
    else if (keycode == KEY_A)
        game->player.l_r = -1;
    else if (keycode == KEY_D)
        game->player.l_r = 1;
    else if (keycode == KEY_LEFT)
        game->player.rot = -1;
    else if (keycode == KEY_RIGHT)
        game->player.rot = 1;
    else if (keycode == KEY_SHIFT)
        game->player.sprint = 1;
    return (0);
}

static int key_release(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        game->player.u_d = 0;
    else if (keycode == KEY_S)
        game->player.u_d = 0;
    else if (keycode == KEY_A)
        game->player.l_r = 0;
    else if (keycode == KEY_D)
        game->player.l_r = 0;
    else if (keycode == KEY_LEFT)
        game->player.rot = 0;
    else if (keycode == KEY_RIGHT)
        game->player.rot = 0;
    else if (keycode == KEY_SHIFT)
        game->player.sprint = 0;
    return (0);
}

int	handle_mouse(int x, int y, t_game *game)
{
    static int	last_x = -1;
    int		delta_x;

    (void)y; // We only care about horizontal mouse movement
    if (last_x == -1)
    {
        last_x = x;
        return (0);
    }

    delta_x = x - last_x;
    if (delta_x != 0)
    {
        // Convert mouse movement to rotation
        // Adjust the multiplier (0.003) to change mouse sensitivity
        game->player.angle += delta_x * 0.003;
        game->player.dir_x = cos(game->player.angle);
        game->player.dir_y = sin(game->player.angle);
        game->player.plane_x = -game->player.dir_y * 0.66;
        game->player.plane_y = game->player.dir_x * 0.66;
    }
    last_x = x;
    return (0);
}

static int	game_loop(t_game *game)
{
    // Update player position and rotation
    move_player(game);
    rotate_player(game);
    // Clear the screen (fill with black)
    ft_memset(game->addr, 0, S_W * S_H * sizeof(int));
    // Cast rays and render the scene
    cast_rays(game);
    render_walls(game);
    render_minimap(game);
    // Put the image to window
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}

void set_hooks(t_game *game)
{
    mlx_hook(game->win, 2, 1L<<0, key_press, game);
    mlx_hook(game->win, 3, 1L<<1, key_release, game);
    mlx_hook(game->win, 6, 1L<<6, handle_mouse, game);
    mlx_hook(game->win, 17, 0, clean_exit_msg, game);
    mlx_loop_hook(game->mlx, game_loop, game);
}
