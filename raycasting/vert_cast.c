/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:17:35 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/09 13:17:40 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Calculate initial intercept points for vertical ray
void init_vertical_intercept(double r_ang, float p_x, float p_y, 
	float *x_intercept, float *y_intercept)
{
	*x_intercept = floor(p_x / SCALE) * SCALE;
	if (cos(r_ang) > 0)
	*x_intercept += SCALE;

	*y_intercept = p_y + (*x_intercept - p_x) * tan(r_ang);
}

// Calculate step sizes for vertical ray casting
void calculate_vertical_steps(double r_ang, float *x_step, float *y_step)
{
	*x_step = SCALE;
	if (cos(r_ang) < 0)
	*x_step *= -1;

	*y_step = SCALE * tan(r_ang);
	if ((sin(r_ang) < 0 && *y_step > 0) || (sin(r_ang) > 0 && *y_step < 0))
	*y_step *= -1;
}

// Check for wall collision in vertical ray casting
bool check_vertical_wall(t_map *map, float next_x, float next_y, double r_ang)
{
	int map_x = floor(next_x / SCALE) - (cos(r_ang) < 0 ? 1 : 0);
	int map_y = floor(next_y / SCALE);

	if (map_x >= 0 && map_x < map->map_w && map_y >= 0 && 
	map_y < map->map_h && map->map[map_y][map_x] == '1')
	return true;

	return false;
}

float continue_vertical_intersection(t_map *map, double r_ang, float p_x, float p_y,
	t_pos *vert_inter, float next_x, float next_y,
	float x_step, float y_step)
{
bool hit_wall = false;
float vert_dist = INFINITY;

while (!hit_wall && next_x >= 0 && next_x < map->map_w * SCALE && 
next_y >= 0 && next_y < map->map_h * SCALE)
{
 if (check_vertical_wall(map, next_x, next_y, r_ang))
 {
	 hit_wall = true;
	 vert_inter->x = next_x;
	 vert_inter->y = next_y;
	 vert_dist = sqrt(pow(vert_inter->x - p_x, 2) + 
	 pow(vert_inter->y - p_y, 2));
 }
 else
 {
	 next_x += x_step;
	 next_y += y_step;
 }
}

return vert_dist;
}

// Find vertical wall intersection
float find_vertical_intersection(t_map *map, double r_ang, float p_x, float p_y, 
	   t_pos *vert_inter)
{
	float vert_dist = INFINITY;
	float x_intercept, y_intercept, x_step, y_step;

	if (cos(r_ang) == 0)
	return INFINITY;

	init_vertical_intercept(r_ang, p_x, p_y, &x_intercept, &y_intercept);
	calculate_vertical_steps(r_ang, &x_step, &y_step);

	float next_x = x_intercept;
	float next_y = y_intercept;

	return continue_vertical_intersection(map, r_ang, p_x, p_y, 
					vert_inter, next_x, next_y, 
					x_step, y_step);
}
