/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:08:30 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/19 18:45:23 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void my_mlx_pixel_put(t_img *img, int x, int y, uint32_t color)
{
    if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
        mlx_put_pixel(img->img, x, y, color);
}

void draw_wall(t_map *map, int offset_x, int offset_y)
{
    for (int y = offset_y; y < offset_y + SCALE; y++)
    {
        for (int x = offset_x; x < offset_x + SCALE; x++)
        {
            my_mlx_pixel_put(&map->img, x, y, 0xFF0000FF); // Red 
        }
    }
}

bool map_has_wall_at(t_map *map, double x, double y)
{
    int map_x = floor(x / SCALE);
    int map_y = floor(y / SCALE);
    
    if (map_x < 0 || map_x >= map->map_w || map_y < 0 || map_y >= map->map_h)
        return true; 
    
    if (map->map[map_y][map_x] == '1')
        return true;
    
    return false;
}

void draw_ceiling(t_map *map, int column, int wall_top)
{
    for (int y = 0; y < wall_top; y++) {
        my_mlx_pixel_put(&map->img, column, y, 0x87CEEBFF); // blue
    }
}

void draw_floor(t_map *map, int column, int wall_bottom)
{
    for (int y = wall_bottom; y < W_HEIGHT; y++) {
        my_mlx_pixel_put(&map->img, column, y, 0x8B4513FF); // Brown
    }
}
