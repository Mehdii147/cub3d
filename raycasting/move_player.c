/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:09:28 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/10 18:31:36 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


void calculate_new_position(t_map *map, float delta_time, double *new_x, double *new_y)
{
    double forward_x = 0;
    double forward_y = 0;
    double strafe_x = 0;
    double strafe_y = 0;
    
    // Calculate forward/backward movement component
    if (map->p_pos.walk_direction != 0)
    {
        float move_step = map->p_pos.walk_direction * SPEED * delta_time;
        forward_x = cos(map->p_pos.ang) * move_step;
        forward_y = sin(map->p_pos.ang) * move_step;
    }
    
    // Calculate sideways movement component
    if (map->p_pos.side_direction != 0)
    {
        float strafe_step = map->p_pos.side_direction * SPEED * delta_time;
        strafe_x = cos(map->p_pos.ang + M_PI/2) * strafe_step;
        strafe_y = sin(map->p_pos.ang + M_PI/2) * strafe_step;
    }
    
    // Combine movements
    *new_x = map->p_pos.x + forward_x + strafe_x;
    *new_y = map->p_pos.y + forward_y + strafe_y;
}

void move_player(t_map *map, float delta_time)
{
    double new_x, new_y;
    
    // Handling rotation move
    map->p_pos.ang += map->p_pos.rotate_direction * ROTATE * delta_time;
    
    // Normalize angle
    if (map->p_pos.ang > 2 * M_PI)
        map->p_pos.ang -= 2 * M_PI;
    if (map->p_pos.ang < 0)
        map->p_pos.ang += 2 * M_PI;
    
    // Calculate new position
    calculate_new_position(map, delta_time, &new_x, &new_y);
    
    // Update position if there's no wall
    if (!map_has_wall_at(map, new_x, new_y))
    {
        map->p_pos.x = new_x;
        map->p_pos.y = new_y;
    }
}

void handle_movement_keys(mlx_key_data_t keydata, t_map *map)
{
    // Forward/backward movement (W/S)
    if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || 
                                  keydata.action == MLX_REPEAT))
        map->p_pos.walk_direction = 1;
    else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || 
                                      keydata.action == MLX_REPEAT))
        map->p_pos.walk_direction = -1;
    else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S) && 
            keydata.action == MLX_RELEASE)
        map->p_pos.walk_direction = 0;
    
    // Strafe movement (A/D)
    else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || 
                                  keydata.action == MLX_REPEAT))
        map->p_pos.side_direction = 1;
    else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || 
                                      keydata.action == MLX_REPEAT))
        map->p_pos.side_direction = -1;
    else if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D) && 
            keydata.action == MLX_RELEASE)
        map->p_pos.side_direction = 0;
}

void handle_rotation_keys(mlx_key_data_t keydata, t_map *map)
{
    // Handle rotation keys
    if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || 
                                      keydata.action == MLX_REPEAT))
        map->p_pos.rotate_direction = 1;
    else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || 
                                         keydata.action == MLX_REPEAT))
        map->p_pos.rotate_direction = -1;
    else if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT) && 
            keydata.action == MLX_RELEASE)
        map->p_pos.rotate_direction = 0;
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_map *map = (t_map *)param;
    
    // Handle movement keys (W, S, A, D)
    handle_movement_keys(keydata, map);
    
    // Handle rotation keys (LEFT, RIGHT)
    handle_rotation_keys(keydata, map);
    
    // Exit on ESC
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(map->mlx);
}
