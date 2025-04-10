/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:06:35 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/10 14:07:09 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int main(void)
{
    t_map map;
    
    char *predefined_map[] = {
        "111111111111111111",
        "100000000000000001",
        "100000000000000001",
        "100000000111111001",
        "100000000000000001",
        "100000000000000001",
        "100000001000000001",
        "100000000000000001",
        "100000000000000001",
        "100000000000000001",
        "100000000011111001",
        "100000000000000001",
        "100000000000000001",
        "111111111111111111"
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
    map.n_textures = "./textures/wall1F.png";
    map.s_textures = "./textures/wall2F.png";
    map.e_textures = "./textures/wall3F.png";
    map.w_textures = "./textures/wall4F.png";
    load_textures(&map);
    map.map_h = 14;
    map.map_w = 18;
    map.map = predefined_map;
    map.p_pos.x = (map.map_w / 2) * SCALE + SCALE / 2;
    map.p_pos.y = (map.map_h / 2) * SCALE - SCALE / 2;
    map.p_pos.ang = 0;  // Initial angle (facing right)
    map.p_pos.walk_direction = 0;
    map.p_pos.rotate_direction = 0;

    mlx_key_hook(map.mlx, key_hook, &map);
    mlx_loop_hook(map.mlx, game_loop, &map);
    mlx_loop(map.mlx);
    mlx_delete_texture(map.textures.north);
    mlx_delete_texture(map.textures.south);
    mlx_delete_texture(map.textures.east);
    mlx_delete_texture(map.textures.west);
    
    mlx_terminate(map.mlx);
    return (EXIT_SUCCESS);
}