/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:06:35 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/22 20:32:20 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_map(t_map *map, t_data *data)
{
	map->data = data;
	load_textures(map);
	map->map_h = map->data->height;
	map->map_w = map->data->width;
	map->map = data->map;
	initialize_position(data, &map->p_pos.x, &map->p_pos.y);
	map->p_pos.ang = update_angle(data);
	map->p_pos.walk_direction = 0;
	map->p_pos.side_direction = 0;
	map->p_pos.rotate_direction = 0;
}

int	initialize_mlx(t_map *map)
{
	map->mlx = mlx_init(W_WIDTH, W_HEIGHT, "Cub3D", false);
	if (!map->mlx)
	{
		fprintf(stderr, "Error initializing MLX42\n");
		return (EXIT_FAILURE);
	}
	map->img.img = mlx_new_image(map->mlx, W_WIDTH, W_HEIGHT);
	if (!map->img.img)
	{
		fprintf(stderr, "Error creating image\n");
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(map->mlx, map->img.img, 0, 0) == -1)
	{
		fprintf(stderr, "Error putting image to window\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_map	map;
	t_cube	cube;

	if (ac != 2)
		ft_error_message("num of args isn't correct.Usage: ./cub3D <map_file>");
	get_cub(&cube);
	cube.data = ft_parsing(av);
	initialize_mlx(&map);
	init_map(&map, cube.data);
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
