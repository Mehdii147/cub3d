
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


double normalize_angle(double r_ang)
{
    while (r_ang < 0)
        r_ang += 2 * M_PI;
    while (r_ang >= 2 * M_PI)
        r_ang -= 2 * M_PI;
    
    return r_ang;
}

// Get the closest intersection point (horizontal or vertical)
t_pos get_best_intersection(t_map *map, double r_ang)
{
    t_pos intersection;
    t_pos horz_inter, vert_inter;
    float horz_dist, vert_dist;
    
    // Get player position
    float p_x = map->p_pos.x;
    float p_y = map->p_pos.y;
    
    // Normalize the angle
    r_ang = normalize_angle(r_ang);
    
    // Find intersections and distances
    horz_dist = find_horizontal_intersection(map, r_ang, p_x, p_y, &horz_inter);
    vert_dist = find_vertical_intersection(map, r_ang, p_x, p_y, &vert_inter);
    
    // Return the closest intersection
    if (horz_dist < vert_dist)
        intersection = horz_inter;
    else
        intersection = vert_inter;
    
    return intersection;
}





// Process a single ray for raycasting
void process_ray(t_map *map, int column, double ray_angle)
{
    // Get intersection points and distances
    t_pos horz_inter, vert_inter;
    float horz_dist = find_horizontal_intersection(map, ray_angle, map->p_pos.x, 
                                                 map->p_pos.y, &horz_inter);
    float vert_dist = find_vertical_intersection(map, ray_angle, map->p_pos.x, 
                                               map->p_pos.y, &vert_inter);
    
    // Determine hit information
    bool is_horz_hit;
    t_pos intersection;
    double distance;
    get_wall_hit_info(horz_dist, vert_dist, horz_inter, vert_inter, 
                    &is_horz_hit, &intersection, &distance);
    
    // Calculate wall dimensions
    int wall_top, wall_bottom;
    double fov = 60 * (M_PI / 180);
    calculate_wall_dimensions(distance, ray_angle, map->p_pos.ang, 
                           fov, &wall_top, &wall_bottom);
    
    // Select and apply texture
    mlx_texture_t *texture = select_texture(map, is_horz_hit, ray_angle);
    int tex_x = calculate_texture_x(is_horz_hit, intersection, texture);
    
    // Draw wall, floor and ceiling
    draw_wall_strip(map, column, wall_top, wall_bottom, texture, tex_x);
    draw_ceiling(map, column, wall_top);
    draw_floor(map, column, wall_bottom);
}

// Main game loop function
void game_loop(void *param)
{
    t_map *map = (t_map *)param;
    static double last_time = 0;
    double current_time = mlx_get_time();
    double delta_time = current_time - last_time;
    last_time = current_time;
    
    clear_screen(map);
    move_player(map, delta_time);
    double fov;
    int num_rays;
    double angle_increment;
    init_ray_casting(&fov, &num_rays, &angle_increment);
    for (int i = 0; i < num_rays; i++)
    {
        double ray_angle = calculate_ray_angle(map->p_pos.ang, fov, angle_increment, i);
        process_ray(map, i, ray_angle);
    }
}

