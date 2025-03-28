
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 03:20:01 by ehafiane          #+#    #+#             */
/*   Updated: 2025/03/14 02:12:20 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/cub3d.h"


float find_horizontal_intersection(t_map *map, double r_ang, float p_x, float p_y, t_pos *horz_inter)
{
    float horz_dist = INFINITY;
    
    // L9aw coordinate y dyal akrab ta9ato3 horizontal
    float y_intercept = floor(p_y / SCALE) * SCALE;
    // Ila ray kaychof lta7t sir lkhat li jay
    if (sin(r_ang) > 0)
        y_intercept += SCALE;
    
    // L9aw el coordinate x dyal akrab ta9ato3 horizontal
    float x_intercept = p_x + (y_intercept - p_y) / tan(r_ang);
    
    // 7sab steps dyal increment
    float y_step = SCALE;
    // Ila ray kaychof lfo9 khassna nmchiw lfo9
    if (sin(r_ang) < 0)
        y_step *= -1;
    
    // 7sab 9imat x-step b trigonometrie
    float x_step = SCALE / tan(r_ang);
    if ((cos(r_ang) < 0 && x_step > 0) || (cos(r_ang) > 0 && x_step < 0))
        x_step *= -1;
    
    // Bda men no9ta lawla dyal ta9ato3
    float next_x = x_intercept;
    float next_y = y_intercept;
    
    // Check wach ray ghadi bsh horizontal
    if (sin(r_ang) == 0)
        return INFINITY;
    
    // Loop bach nl9aw fin ghadi n9iss l7ayt
    bool hit_wall = false;
    while (!hit_wall && next_x >= 0 && next_x < map->map_w * SCALE && 
           next_y >= 0 && next_y < map->map_h * SCALE)
    {
        // 7sab lkhana li ghadine ncheckiw
        int map_x = floor(next_x / SCALE);
        // Ila ray kaychof lfo9, check khana wa7da lfo9
        int map_y = floor(next_y / SCALE) - (sin(r_ang) < 0 ? 1 : 0);
        
        // Check wach lkhana fiha 7it
        if (map_x >= 0 && map_x < map->map_w && map_y >= 0 && map_y < map->map_h && 
            map->map[map_y][map_x] == '1')
        {
            hit_wall = true;
            horz_inter->x = next_x;
            horz_inter->y = next_y;
            horz_dist = sqrt(pow(horz_inter->x - p_x, 2) + pow(horz_inter->y - p_y, 2));
        }
        else
        {
            // Ila makan 7ta 7it zid sir l9oddam
            next_x += x_step;
            next_y += y_step;
        }
    }
    
    return horz_dist;
}

float find_vertical_intersection(t_map *map, double r_ang, float p_x, float p_y, t_pos *vert_inter)
{
    float vert_dist = INFINITY;
    
    // L9aw  lcoordinate x dyal akrab ta9ato3 vertical
    float x_intercept = floor(p_x / SCALE) * SCALE;
    // Ila ray kaychof limene sir lkhat li jay
    if (cos(r_ang) > 0)
        x_intercept += SCALE;
    
    // L9aw lcoordinate y dyal akrab ta9ato3 vertical
    float y_intercept = p_y + (x_intercept - p_x) * tan(r_ang);
    
    // 7sab steps dyal zi7f
    float x_step = SCALE;
    // Ila ray kaychof lisar khassna nmchiw lisar
    if (cos(r_ang) < 0)
        x_step *= -1;
    
    // 7sab 9imat y-step b trigonometrie
    float y_step = SCALE * tan(r_ang);
    if ((sin(r_ang) < 0 && y_step > 0) || (sin(r_ang) > 0 && y_step < 0))
        y_step *= -1;
    
    // Bda men no9ta lawla dyal ta9ato3
    float next_x = x_intercept;
    float next_y = y_intercept;
    
    // Check wach ray ghadi bsh vertical
    if (cos(r_ang) == 0)
        return INFINITY;
    
    // Loop bach nl9aw fin ghadi n9is l7ayt
    bool hit_wall = false;
    while (!hit_wall && next_x >= 0 && next_x < map->map_w * SCALE && 
           next_y >= 0 && next_y < map->map_h * SCALE)
    {
        // 7sab lkhana li ghadine ncheckiw
        // Ila kaychof lisar check khana wa7da lisar
        int map_x = floor(next_x / SCALE) - (cos(r_ang) < 0 ? 1 : 0);
        int map_y = floor(next_y / SCALE);
        
        // Check wach lkhana fiha 7it
        if (map_x >= 0 && map_x < map->map_w && map_y >= 0 && map_y < map->map_h && 
            map->map[map_y][map_x] == '1')
        {
            hit_wall = true;
            vert_inter->x = next_x;
            vert_inter->y = next_y;
            vert_dist = sqrt(pow(vert_inter->x - p_x, 2) + pow(vert_inter->y - p_y, 2));
        }
        else
        {
            // Ila makan 7ta 7it zid sir l9oddam
            next_x += x_step;
            next_y += y_step;
        }
    }
    
    return vert_dist;
}

t_pos get_best_intersection(t_map *map, double r_ang)
{
    t_pos intersection;
    t_pos horz_inter, vert_inter;
    float horz_dist = INFINITY, vert_dist = INFINITY;
    
    // pos dyal player
    float p_x = map->p_pos.x;
    float p_y = map->p_pos.y;
    
    // normalis the angle
    while (r_ang < 0)
        r_ang += 2 * M_PI;
    while (r_ang >= 2 * M_PI)
        r_ang -= 2 * M_PI;
    
    // L9aw ta9ato3at horizontal o vertical
    horz_dist = find_horizontal_intersection(map, r_ang, p_x, p_y, &horz_inter);
    vert_dist = find_vertical_intersection(map, r_ang, p_x, p_y, &vert_inter);
    
    // Reje3 ta9ato3 li huwa 9rib
    if (horz_dist < vert_dist)
        intersection = horz_inter;
    else
        intersection = vert_inter;
    
    return intersection;
}


int abs(int n) { return ((n > 0) ? n : (n * (-1))); }
void DDA(t_pos p_pos, t_pos inter_pos, t_map *map)
{
    // 7seb dx o dy
    int dx = inter_pos.x - p_pos.x;
    int dy = inter_pos.y - p_pos.y;
 
    // 7seb steps li khassna bch n7to pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // 7seb increment f x o y lkol step
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
 
    
    float X = p_pos.x;
    float Y = p_pos.y;
    for (int i = 0; i <= steps; i++) {
        my_mlx_pixel_put(&map->img, round(X), round(Y),0x00FF00FF); // 7ot pixel f (X,Y)
        X += Xinc; 
        Y += Yinc;
    }
}



// void game_loop(void *param)
// {
//     t_map *map = (t_map *)param;
//     static double last_time = 0;
//     double current_time = mlx_get_time();
//     double delta_time = current_time - last_time;
//     last_time = current_time;
    
//     // Clear screen
//     for (int i = 0; i < W_WIDTH * W_HEIGHT; i++)
//         mlx_put_pixel(map->img.img, i % W_WIDTH, i / W_WIDTH, 0x0FFFFF0F);
    
//     // Move player
//     move_player(map, delta_time);
    
//     // Draw map
//     draw_map(map);
    
//     // Define FOV and number of rays
//     double fov = 60 * (M_PI / 180); // Convert FOV to radians
//     int num_rays = W_WIDTH; // Number of rays to cast (one per pixel column)
//     double angle_increment = fov / num_rays;
    
//     // Cast rays within the FOV
//     for (int i = 0; i < num_rays; i++)
//     {
//         double ray_angle = map->p_pos.ang - (fov / 2) + (i * angle_increment);
//         t_pos intersection = get_best_intersection(map, ray_angle);
//         DDA(map->p_pos, intersection, map);
//     }
    
//     // Draw player
//     draw_player(map);
// }





void game_loop(void *param)
{
    t_map *map = (t_map *)param;
    static double last_time = 0;
    double current_time = mlx_get_time();
    double delta_time = current_time - last_time;
    last_time = current_time;
    
    // Clear screen
    for (int i = 0; i < W_WIDTH * W_HEIGHT; i++)
        mlx_put_pixel(map->img.img, i % W_WIDTH, i / W_WIDTH, 0x0FFFFF0F);
    
    // Move player
    move_player(map, delta_time);
    
    // Draw map (2D minimap)
    // draw_map(map);
    
    // Define FOV and number of rays
    double fov = 60 * (M_PI / 180); // Convert FOV to radians
    int num_rays = W_WIDTH; // Number of rays to cast (one per pixel column)
    double angle_increment = fov / num_rays;
    
    // Cast rays within the FOV
    for (int i = 0; i < num_rays; i++)
    {
        double ray_angle = map->p_pos.ang - (fov / 2) + (i * angle_increment);
        t_pos intersection = get_best_intersection(map, ray_angle);
        
        // Calculate distance to the wall (corrected for fisheye effect)
        double distance = sqrt(pow(intersection.x - map->p_pos.x, 2) + pow(intersection.y - map->p_pos.y, 2));
        distance *= cos(ray_angle - map->p_pos.ang); // Fisheye correction
        
        // Calculate wall height
        double wall_height = (SCALE / distance) * (W_WIDTH / 2) / tan(fov / 2);
        
        // Calculate the top and bottom of the wall on the screen
        int wall_top = (W_HEIGHT / 2) - (wall_height / 2);
        int wall_bottom = (W_HEIGHT / 2) + (wall_height / 2);
        
        // Draw the wall column
        for (int y = wall_top; y < wall_bottom; y++)
        {
            // Set the color of the wall (e.g., red for now)
            uint32_t color = 0xD3D3D3FF; // Light grey color (RGBA)
            my_mlx_pixel_put(&map->img, i, y, color);
        }
    }
    
    // Draw player (2D minimap)
    // draw_player(map);
}