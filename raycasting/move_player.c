/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:09:28 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/09 13:05:18 by ehafiane         ###   ########.fr       */
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

