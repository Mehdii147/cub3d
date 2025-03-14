/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:09:28 by ehafiane          #+#    #+#             */
/*   Updated: 2025/03/14 02:32:46 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


void move_player(t_map *map, float delta_time)
{
    float move_step;
    double new_x, new_y;
    
    // Handling rotation move
    map->p_pos.ang += map->p_pos.rotate_direction * ROTATE * delta_time;
    
    // Normalize angle
    if (map->p_pos.ang > 2 * M_PI)
        map->p_pos.ang -= 2 * M_PI;
    if (map->p_pos.ang < 0)
        map->p_pos.ang += 2 * M_PI;
    
    // Calculate movement based on angle and speed
    move_step = map->p_pos.walk_direction * SPEED * delta_time;
    new_x = map->p_pos.x + cos(map->p_pos.ang) * move_step;
    new_y = map->p_pos.y + sin(map->p_pos.ang) * move_step;
    
    // Update position if there's no wall
    if (!map_has_wall_at(map, new_x, new_y))
    {
        map->p_pos.x = new_x;
        map->p_pos.y = new_y;
    }
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_map *map = (t_map *)param;
    
    // Handle movement keys
    if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        map->p_pos.walk_direction = 1;
    else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        map->p_pos.walk_direction = -1;
    else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S) && keydata.action == MLX_RELEASE)
        map->p_pos.walk_direction = 0;
    
    // Handle rotation keys
    if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        map->p_pos.rotate_direction = 1;
    else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        map->p_pos.rotate_direction = -1;
    else if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT) && keydata.action == MLX_RELEASE)
        map->p_pos.rotate_direction = 0;
    
    // Exit on ESC
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(map->mlx);
}


void draw_player(t_map *map)
{
    int player_size = 8;
    int player_x = (int)map->p_pos.x;
    int player_y = (int)map->p_pos.y;
    
    // Draw player as a circle
    for (int y = -player_size; y < player_size; y++)
    {
        for (int x = -player_size; x < player_size; x++)
        {
            if (x*x + y*y <= player_size*player_size)
                my_mlx_pixel_put(&map->img, player_x + x, player_y + y, 0x00FF00FF); // Green player
        }
    }
    
    // Draw direction line
    int line_length = 20;
    // int end_x = player_x + cos(map->p_pos.ang) * line_length;
    // int end_y = player_y + sin(map->p_pos.ang) * line_length;
    
    // Draw a line from player to direction
    for (int t = 0; t < line_length; t++)
    {
        int x = player_x + cos(map->p_pos.ang) * t;
        int y = player_y + sin(map->p_pos.ang) * t;
        my_mlx_pixel_put(&map->img, x, y, 0x00FF00FF); // Yellow direction line
    }
}