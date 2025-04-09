/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:08:30 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/09 13:18:51 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, uint32_t color)
{
    if (x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
        mlx_put_pixel(data->img, x, y, color);
}


void draw_wall(t_map *map, int offset_x, int offset_y)
{
    for (int y = offset_y; y < offset_y + SCALE; y++)
    {
        for (int x = offset_x; x < offset_x + SCALE; x++)
        {
            my_mlx_pixel_put(&map->img, x, y, 0xFF0000FF); // Red walls (RGBA)
        }
    }
}


bool map_has_wall_at(t_map *map, double x, double y)
{
    // Convert real coordinates to map grid coordinates
    int map_x = floor(x / SCALE);
    int map_y = floor(y / SCALE);
    
    // Check if the coordinates are within the map boundaries
    if (map_x < 0 || map_x >= map->map_w || map_y < 0 || map_y >= map->map_h)
        return true; // Consider outside the map as a wall
    
    // Check if the grid position is a wall ('1')
    if (map->map[map_y][map_x] == '1')
        return true;
    
    return false;
}

// Draw ceiling
void draw_ceiling(t_map *map, int column, int wall_top)
{
    for (int y = 0; y < wall_top; y++) {
        my_mlx_pixel_put(&map->img, column, y, 0x87CEEBFF); // Sky blue
    }
}

// Draw floor
void draw_floor(t_map *map, int column, int wall_bottom)
{
    for (int y = wall_bottom; y < W_HEIGHT; y++) {
        my_mlx_pixel_put(&map->img, column, y, 0x8B4513FF); // Brown
    }
}
