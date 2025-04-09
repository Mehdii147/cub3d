/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horiz_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:16:50 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/09 13:16:55 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Calculate initial intercept points for horizontal ray
void init_horizontal_intercept(double r_ang, float p_x, float p_y, 
	float *y_intercept, float *x_intercept)
{
	*y_intercept = floor(p_y / SCALE) * SCALE;
	if (sin(r_ang) > 0)
	*y_intercept += SCALE;

	*x_intercept = p_x + (*y_intercept - p_y) / tan(r_ang);
}

// Calculate step sizes for horizontal ray casting
void calculate_horizontal_steps(double r_ang, float *y_step, float *x_step)
{
	*y_step = SCALE;
	if (sin(r_ang) < 0)
	*y_step *= -1;

	*x_step = SCALE / tan(r_ang);
	if ((cos(r_ang) < 0 && *x_step > 0) || (cos(r_ang) > 0 && *x_step < 0))
		*x_step *= -1;
	}

	// Check for wall collision in horizontal ray casting
bool check_horizontal_wall(t_map *map, float next_x, float next_y, double r_ang)
{
	int map_x = floor(next_x / SCALE);
	int map_y = floor(next_y / SCALE) - (sin(r_ang) < 0 ? 1 : 0);

	if (map_x >= 0 && map_x < map->map_w && map_y >= 0 && 
	map_y < map->map_h && map->map[map_y][map_x] == '1')
	return true;

	return false;
}

float continue_horizontal_intersection(t_map *map, double r_ang, float p_x, float p_y,
	t_pos *horz_inter, float next_x, float next_y,
	float x_step, float y_step)
{
	bool hit_wall = false;
	float horz_dist = INFINITY;

	while (!hit_wall && next_x >= 0 && next_x < map->map_w * SCALE && 
	next_y >= 0 && next_y < map->map_h * SCALE)
	{
		if (check_horizontal_wall(map, next_x, next_y, r_ang))
		{
			hit_wall = true;
			horz_inter->x = next_x;
			horz_inter->y = next_y;
			horz_dist = sqrt(pow(horz_inter->x - p_x, 2) + 
			pow(horz_inter->y - p_y, 2));
		}
		else
		{
			next_x += x_step;
			next_y += y_step;
		}
	}
	return horz_dist;
}

	// Find horizontal wall intersection
float find_horizontal_intersection(t_map *map, double r_ang, float p_x, float p_y, 
		t_pos *horz_inter)
{
	float horz_dist = INFINITY;
	float y_intercept, x_intercept, y_step, x_step;

	if (sin(r_ang) == 0)
	return INFINITY;

	init_horizontal_intercept(r_ang, p_x, p_y, &y_intercept, &x_intercept);
	calculate_horizontal_steps(r_ang, &y_step, &x_step);

	float next_x = x_intercept;
	float next_y = y_intercept;

	return continue_horizontal_intersection(map, r_ang, p_x, p_y, 
					horz_inter, next_x, next_y, 
					x_step, y_step);
}
