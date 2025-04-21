/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:58:18 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/21 12:45:07 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	load_textures(t_map *map)
{
	map->textures.north = mlx_load_png(map->data->no);
	if (!map->textures.north)
	{
		fprintf(stderr, "Failed to load north texture: %s\n", map->n_textures);
		exit(EXIT_FAILURE);
	}
	map->textures.south = mlx_load_png(map->data->so);
	if (!map->textures.south)
	{
		fprintf(stderr, "Failed to load south texture: %s\n", map->s_textures);
		exit(EXIT_FAILURE);
	}
	map->textures.east = mlx_load_png(map->data->we);
	if (!map->textures.east)
	{
		fprintf(stderr, "Failed to load east texture: %s\n", map->e_textures);
		exit(EXIT_FAILURE);
	}
	map->textures.west = mlx_load_png(map->data->ea);
	if (!map->textures.west)
	{
		fprintf(stderr, "Failed to load west texture: %s\n", map->w_textures);
		exit(EXIT_FAILURE);
	}
}

void	calculate_wall_dimensions(t_map *map, double ray_angle,
			double player_angle)
{
	double	wall_height;

	map->p_pos.distance *= cos(ray_angle - player_angle);
	wall_height = (SCALE / map->p_pos.distance)
		* (W_HEIGHT / 2) / tan(FOV_R / 2);
	map->p_pos.wall_top = W_HEIGHT / 2 - (wall_height / 2);
	map->p_pos.wall_bottom = W_HEIGHT / 2 + (wall_height / 2);
}

mlx_texture_t	*select_texture(t_map *map, double ray_angle)
{
	if (map->p_pos.is_horz_hit)
	{
		if (sin(ray_angle) > 0)
			return (map->textures.south);
		else
			return (map->textures.north);
	}
	else
	{
		if (cos(ray_angle) > 0)
			return (map->textures.east);
		else
			return (map->textures.west);
	}
}

int	calculate_texture_x(t_map *map, t_pos intersection, mlx_texture_t *texture)
{
	int	tex_x;

	if (map->p_pos.is_horz_hit)
	{
		tex_x = (int)(intersection.x) % SCALE;
	}
	else
	{
		tex_x = (int)(intersection.y) % SCALE;
	}
	tex_x = (tex_x * texture->width) / SCALE;
	return (tex_x);
}

void	draw_wall_strip(t_map *map, int column,
			mlx_texture_t *texture, int tex_x)
{
	int			y;
	int			vertical_end;
	int			tex_y;
	uint8_t		*pixel;

	y = map->p_pos.wall_top;
	if (y < 0)
		y = 0;
	vertical_end = map->p_pos.wall_bottom;
	if (vertical_end > W_HEIGHT)
		vertical_end = W_HEIGHT;
	while (y < vertical_end)
	{
		tex_y = ((y - map->p_pos.wall_top) * texture->height)
			/ (map->p_pos.wall_bottom - map->p_pos.wall_top);
		pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
		my_mlx_pixel_put(&map->img, column, y,
			(pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3]);
		y++;
	}
}
