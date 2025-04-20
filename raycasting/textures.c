/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:58:18 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/20 17:47:41 by ehafiane         ###   ########.fr       */
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

void	calculate_wall_dimensions(double distance, double ray_angle,
			double player_angle, double fov, int *wall_top, int *wall_bottom)
{
	distance *= cos(ray_angle - player_angle); // Fisheye correction
	double wall_height = (SCALE / distance) * (W_HEIGHT / 2) / tan(fov / 2);
	*wall_top = W_HEIGHT / 2 - (wall_height / 2);
	*wall_bottom = W_HEIGHT / 2 + (wall_height / 2);
}

// Select the appropriate texture based on which wall was hit
mlx_texture_t *select_texture(t_map *map, bool is_horz_hit, double ray_angle)
{
	if (is_horz_hit)
	{
		// Horizontal hit - north or south wall
		return (sin(ray_angle) > 0) ? map->textures.south : map->textures.north;
	} else{
		// Vertical hit - east or west wall
		return (cos(ray_angle) > 0) ? map->textures.east : map->textures.west;
	}
}

// Calculate texture x-coordinate
int calculate_texture_x(bool is_horz_hit, t_pos intersection, mlx_texture_t *texture)
{
	int tex_x;

	if (is_horz_hit) {
		// For horizontal intersections, use the x-coordinate
		tex_x = (int)(intersection.x) % SCALE;
	} else {
		// For vertical intersections, use the y-coordinate
		tex_x = (int)(intersection.y) % SCALE;
	}

	// Convert to texture space
	tex_x = (tex_x * texture->width) / SCALE;
	return tex_x;
}

// Draw textured wall strip
void draw_wall_strip(t_map *map, int column, int wall_top, int wall_bottom,
				   mlx_texture_t *texture, int tex_x)
{
	int vertical_start = wall_top > 0 ? wall_top : 0;
	int vertical_end = wall_bottom < W_HEIGHT ? wall_bottom : W_HEIGHT;

	for (int y = vertical_start; y < vertical_end; y++) {
		// Calculate texture y-coordinate
		int tex_y = ((y - wall_top) * texture->height) / (wall_bottom - wall_top);

		// Get color from texture
		uint8_t *pixel = &texture->pixels[(tex_y * texture->width + tex_x) * 4];
		uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];

		my_mlx_pixel_put(&map->img, column, y, color);
	}
}