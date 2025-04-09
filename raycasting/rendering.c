/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:15:57 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/09 13:23:48 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


// Initialize ray casting variables
void init_ray_casting(double player_angle, double *fov, int *num_rays, double *angle_increment)
{
    *fov = 60 * (M_PI / 180); // Convert to radians
    *num_rays = W_WIDTH; // Number of rays to cast (one per pixel column)
    *angle_increment = *fov / *num_rays;
}

// Clear the screen
void clear_screen(t_map *map)
{
    for (int i = 0; i < W_WIDTH * W_HEIGHT; i++)
        mlx_put_pixel(map->img.img, i % W_WIDTH, i / W_WIDTH, 0x0FFFFF0F);
}

// Calculate ray angle for current column
double calculate_ray_angle(double player_angle, double fov, double angle_increment, int column)
{
    return player_angle - (fov / 2) + (column * angle_increment);
}

// Determine which wall was hit and get hit position
void get_wall_hit_info(float horz_dist, float vert_dist, t_pos horz_inter, 
                     t_pos vert_inter, bool *is_horz_hit, t_pos *intersection, 
                     double *distance)
{
    *is_horz_hit = (horz_dist < vert_dist);
    *intersection = *is_horz_hit ? horz_inter : vert_inter;
    *distance = *is_horz_hit ? horz_dist : vert_dist;
}
