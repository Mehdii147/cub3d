/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:06:35 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/08 20:29:31 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

void load_textures(t_map *map)
{
    // Load north texture
    map->textures.north = mlx_load_png(map->n_textures);
    if (!map->textures.north) {
        fprintf(stderr, "Failed to load north texture: %s\n", map->n_textures);
        exit(EXIT_FAILURE);
    }

    // Load south texture
    map->textures.south = mlx_load_png(map->s_textures);
    if (!map->textures.south) {
        fprintf(stderr, "Failed to load south texture: %s\n", map->s_textures);
        exit(EXIT_FAILURE);
    }

    // Load east texture
    map->textures.east = mlx_load_png(map->e_textures);
    if (!map->textures.east) {
        fprintf(stderr, "Failed to load east texture: %s\n", map->e_textures);
        exit(EXIT_FAILURE);
    }

    // Load west texture
    map->textures.west = mlx_load_png(map->w_textures);
    if (!map->textures.west) {
        fprintf(stderr, "Failed to load west texture: %s\n", map->w_textures);
        exit(EXIT_FAILURE);
    }
    
    printf("All textures loaded successfully!\n");
}


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
    map.n_textures = "/Users/mehdi/1337/cub3dm/textures/wall1F.png";
    map.s_textures = "/Users/mehdi/1337/cub3dm/textures/wall2F.png";
    map.e_textures = "/Users/mehdi/1337/cub3dm/textures/wall3F.png";
    map.w_textures = "/Users/mehdi/1337/cub3dm/textures/wall4F.png";
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