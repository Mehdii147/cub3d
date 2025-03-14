/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:06:35 by ehafiane          #+#    #+#             */
/*   Updated: 2025/03/14 02:06:55 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int main(void)
{
    t_map map;
    char *predefined_map[] = {
        "1111111111111",
        "1000000000001",
        "1000000000001",
        "1000000000001",
        "1000001000001",
        "1000000000001",
        "1000000000001",
        "1000000000001",
        "1111111111111"
    };

    map.mlx = mlx_init(W_WIDTH, W_HEIGHT, "Cub3D", false);
    if (!map.mlx)
    {
        fprintf(stderr, "Error initializing MLX42\n");
        return (EXIT_FAILURE);
    }

    map.img.img = mlx_new_image(map.mlx, W_WIDTH, W_HEIGHT);
    if (!map.img.img)
    {
        fprintf(stderr, "Error creating image\n");
        return (EXIT_FAILURE);
    }

    if (mlx_image_to_window(map.mlx, map.img.img, 0, 0) == -1)
    {
        fprintf(stderr, "Error putting image to window\n");
        return (EXIT_FAILURE);
    }

    map.map_h = 9;
    map.map_w = 13;
    map.map = predefined_map;
    
    // Initialize player position (middle of the map)
    map.p_pos.x = (map.map_w / 2) * SCALE + SCALE / 2;
    map.p_pos.y = (map.map_h / 2) * SCALE - SCALE / 2;
    map.p_pos.ang = 0;  // Initial angle (facing right)
    map.p_pos.walk_direction = 0;
    map.p_pos.rotate_direction = 0;

    // Register hooks
    mlx_key_hook(map.mlx, key_hook, &map);
    mlx_loop_hook(map.mlx, game_loop, &map);

    mlx_loop(map.mlx);
    mlx_terminate(map.mlx);
    return (EXIT_SUCCESS);
}