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
    
    // Find the y-coordinate of the closest horizontal grid intersection
    float y_intercept = floor(p_y / SCALE) * SCALE;
    // If ray is facing down, move to the next grid line
    if (sin(r_ang) > 0)
        y_intercept += SCALE;
    
    // Find the x-coordinate of the closest horizontal grid intersection
    float x_intercept = p_x + (y_intercept - p_y) / tan(r_ang);
    
    // Calculate the increment steps
    float y_step = SCALE;
    // If ray is facing up, we need to step upward in the grid
    if (sin(r_ang) < 0)
        y_step *= -1;
    
    // Calculate the x-step value using trigonometry
    float x_step = SCALE / tan(r_ang);
    if ((cos(r_ang) < 0 && x_step > 0) || (cos(r_ang) > 0 && x_step < 0))
        x_step *= -1;
    
    // Start the next intersection at the first intersection point
    float next_x = x_intercept;
    float next_y = y_intercept;
    
    // Check if the ray is exactly horizontal
    if (sin(r_ang) == 0)
        return INFINITY;
    
    // Loop to find the wall hit
    bool hit_wall = false;
    while (!hit_wall && next_x >= 0 && next_x < map->map_w * SCALE && 
           next_y >= 0 && next_y < map->map_h * SCALE)
    {
        // Calculate the grid cell to check
        int map_x = floor(next_x / SCALE);
        // If looking up, check one cell up
        int map_y = floor(next_y / SCALE) - (sin(r_ang) < 0 ? 1 : 0);
        
        // Check if the cell is a wall
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
            // If no wall, move to next intersection
            next_x += x_step;
            next_y += y_step;
        }
    }
    
    return horz_dist;
}

float find_vertical_intersection(t_map *map, double r_ang, float p_x, float p_y, t_pos *vert_inter)
{
    float vert_dist = INFINITY;
    
    // Find the x-coordinate of the closest vertical grid intersection
    float x_intercept = floor(p_x / SCALE) * SCALE;
    // If ray is facing right, move to the next grid line
    if (cos(r_ang) > 0)
        x_intercept += SCALE;
    
    // Find the y-coordinate of the closest vertical grid intersection
    float y_intercept = p_y + (x_intercept - p_x) * tan(r_ang);
    
    // Calculate the increment steps
    float x_step = SCALE;
    // If ray is facing left, we need to step leftward in the grid
    if (cos(r_ang) < 0)
        x_step *= -1;
    
    // Calculate the y-step value using trigonometry
    float y_step = SCALE * tan(r_ang);
    if ((sin(r_ang) < 0 && y_step > 0) || (sin(r_ang) > 0 && y_step < 0))
        y_step *= -1;
    
    // Start the next intersection at the first intersection point
    float next_x = x_intercept;
    float next_y = y_intercept;
    
    // Check if the ray is exactly vertical
    if (cos(r_ang) == 0)
        return INFINITY;
    
    // Loop to find the wall hit
    bool hit_wall = false;
    while (!hit_wall && next_x >= 0 && next_x < map->map_w * SCALE && 
           next_y >= 0 && next_y < map->map_h * SCALE)
    {
        // Calculate the grid cell to check
        // If looking left, check one cell left
        int map_x = floor(next_x / SCALE) - (cos(r_ang) < 0 ? 1 : 0);
        int map_y = floor(next_y / SCALE);
        
        // Check if the cell is a wall
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
            // If no wall, move to next intersection
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
    
    // Player position
    float p_x = map->p_pos.x;
    float p_y = map->p_pos.y;
    
    // Normalize angle
    while (r_ang < 0)
        r_ang += 2 * M_PI;
    while (r_ang >= 2 * M_PI)
        r_ang -= 2 * M_PI;
    
    // Find horizontal and vertical intersections
    horz_dist = find_horizontal_intersection(map, r_ang, p_x, p_y, &horz_inter);
    vert_dist = find_vertical_intersection(map, r_ang, p_x, p_y, &vert_inter);
    
    // Return the closest intersection
    if (horz_dist < vert_dist)
        intersection = horz_inter;
    else
        intersection = vert_inter;
    
    return intersection;
}


int abs(int n) { return ((n > 0) ? n : (n * (-1))); }
void DDA(t_pos p_pos, t_pos inter_pos, t_map *map)
{
    // calculate dx & dy
    int dx = inter_pos.x - p_pos.x;
    int dy = inter_pos.y - p_pos.y;
 
    // calculate steps required for generating pixels
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
    // calculate increment in x & y for each steps
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
 
    // Put pixel for each step
    float X = p_pos.x;
    float Y = p_pos.y;
    for (int i = 0; i <= steps; i++) {
        my_mlx_pixel_put(&map->img, round(X), round(Y),0x00FF00FF); // put pixel at (X,Y)
        X += Xinc; // increment in x at each step
        Y += Yinc; // increment in y at each step
    }
}


void game_loop(void *param)
{
    t_map *map = (t_map *)param;
    static double last_time = 0;
    double current_time = mlx_get_time();
    double delta_time = current_time - last_time;
    last_time = current_time;
    
    // Clear the screen
    for (int i = 0; i < W_WIDTH * W_HEIGHT; i++)
        mlx_put_pixel(map->img.img, i % W_WIDTH, i / W_WIDTH, 0x0FFFFF0F);
    
    // Move player
    move_player(map, delta_time);
    
    // Draw map
    draw_map(map);
    DDA(map->p_pos, get_best_intersection(map, map->p_pos.ang), map);

    // Draw player
    draw_player(map);
}


