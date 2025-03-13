/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 03:20:01 by ehafiane          #+#    #+#             */
/*   Updated: 2025/03/13 18:00:26 by ehafiane         ###   ########.fr       */
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

void draw_map(t_map *map)
{
    for (int i = 0; i < map->map_h; i++)
    {
        for (int j = 0; j < map->map_w; j++)
        {
            if (map->map[i][j] == '1')
                draw_wall(map, j * SCALE, i * SCALE);
        }
    }
}

void draw_image(void *param)
{
    t_map *map = (t_map *)param;
    draw_map(map);
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

void move_player(t_map *map, float delta_time)
{
    float move_step;
    double new_x, new_y;
    
    // Handling rotation move
    map->p_pos.ang += map->p_pos.rotate_direction * ROTATE * delta_time;
    
    // Normalize angle
    if (map->p_pos.ang > 2 * M_PI)
        map->p_pos.ang -= 2 * M_PI;
    if (map->p_pos.ang < 0)
        map->p_pos.ang += 2 * M_PI;
    
    // Calculate movement based on angle and speed
    move_step = map->p_pos.walk_direction * SPEED * delta_time;
    new_x = map->p_pos.x + cos(map->p_pos.ang) * move_step;
    new_y = map->p_pos.y + sin(map->p_pos.ang) * move_step;
    
    // Update position if there's no wall
    if (!map_has_wall_at(map, new_x, new_y))
    {
        map->p_pos.x = new_x;
        map->p_pos.y = new_y;
    }
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_map *map = (t_map *)param;
    
    // Handle movement keys
    if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        map->p_pos.walk_direction = 1;
    else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        map->p_pos.walk_direction = -1;
    else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S) && keydata.action == MLX_RELEASE)
        map->p_pos.walk_direction = 0;
    
    // Handle rotation keys
    if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        map->p_pos.rotate_direction = 1;
    else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        map->p_pos.rotate_direction = -1;
    else if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT) && keydata.action == MLX_RELEASE)
        map->p_pos.rotate_direction = 0;
    
    // Exit on ESC
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(map->mlx);
}


void draw_player(t_map *map)
{
    int player_size = 8;
    int player_x = (int)map->p_pos.x;
    int player_y = (int)map->p_pos.y;
    
    // Draw player as a circle
    for (int y = -player_size; y < player_size; y++)
    {
        for (int x = -player_size; x < player_size; x++)
        {
            if (x*x + y*y <= player_size*player_size)
                my_mlx_pixel_put(&map->img, player_x + x, player_y + y, 0x00FF00FF); // Green player
        }
    }
    
    // Draw direction line
    int line_length = 20;
    int end_x = player_x + cos(map->p_pos.ang) * line_length;
    int end_y = player_y + sin(map->p_pos.ang) * line_length;
    
    // Draw a line from player to direction
    for (int t = 0; t < line_length; t++)
    {
        int x = player_x + cos(map->p_pos.ang) * t;
        int y = player_y + sin(map->p_pos.ang) * t;
        my_mlx_pixel_put(&map->img, x, y, 0x00FF00FF); // Yellow direction line
    }
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
    
    // HORIZONTAL RAY-GRID INTERSECTION CODE
    {
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
            horz_dist = INFINITY;
        else
        {
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
                    horz_inter.x = next_x;
                    horz_inter.y = next_y;
                    horz_dist = sqrt(pow(horz_inter.x - p_x, 2) + pow(horz_inter.y - p_y, 2));
                }
                else
                {
                    // If no wall, move to next intersection
                    next_x += x_step;
                    next_y += y_step;
                }
            }
        }
    }
    
    // VERTICAL RAY-GRID INTERSECTION CODE
    {
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
            vert_dist = INFINITY;
        else
        {
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
                    vert_inter.x = next_x;
                    vert_inter.y = next_y;
                    vert_dist = sqrt(pow(vert_inter.x - p_x, 2) + pow(vert_inter.y - p_y, 2));
                }
                else
                {
                    // If no wall, move to next intersection
                    next_x += x_step;
                    next_y += y_step;
                }
            }
        }
    }
    
    // Return the closest intersection
    if (horz_dist < vert_dist)
    {
        intersection = horz_inter;
    }
    else
    {
        intersection = vert_inter;
    }
    
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






int main(void)
{
    t_map map;
    char *predefined_map[] = {
        "1111111111111",
        "1000000000001",
        "1000000000001",
        "1000000000001",
        "1000001000001",
        "1000000000001",
        "1000000000001",
        "1000000000001",
        "1111111111111"
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

    map.map_h = 9;
    map.map_w = 13;
    map.map = predefined_map;
    
    // Initialize player position (middle of the map)
    map.p_pos.x = (map.map_w / 2) * SCALE + SCALE / 2;
    map.p_pos.y = (map.map_h / 2) * SCALE - SCALE / 2;
    map.p_pos.ang = 0;  // Initial angle (facing right)
    map.p_pos.walk_direction = 0;
    map.p_pos.rotate_direction = 0;

    // Register hooks
    mlx_key_hook(map.mlx, key_hook, &map);
    mlx_loop_hook(map.mlx, game_loop, &map);

    mlx_loop(map.mlx);
    mlx_terminate(map.mlx);
    return (EXIT_SUCCESS);
}