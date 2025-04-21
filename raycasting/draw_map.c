/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:08:30 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/21 11:07:05 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, uint32_t color)
{
	if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
		mlx_put_pixel(img->img, x, y, color);
}

bool	map_has_wall_at(t_map *map, double x, double y)
{
	int	map_x ;
	int	map_y ;

	map_x = floor(x / SCALE);
	map_y = floor(y / SCALE);
	if (map_x < 0 || map_x >= map->map_w || map_y < 0 || map_y >= map->map_h)
		return (true);
	if (map->map[map_y][map_x] == '1')
		return (true);
	return (false);
}

void	draw_ceiling(t_map *map, int column)
{
	int	y;

	y = 0;
	while (y < map->p_pos.wall_top)
	{
		my_mlx_pixel_put(&map->img, column, y, map->data->c_color);
		y++;
	}
}

void	draw_floor(t_map *map, int column)
{
	int	y;

	y = map->p_pos.wall_bottom;
	while (y < W_HEIGHT)
	{
		my_mlx_pixel_put(&map->img, column, y, map->data->f_c);
		y++;
	}
}
