/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:17:35 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/21 14:27:01 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_vertical_intercept(double r_ang, t_map *map)
{
	map->p_pos.x_intercept_v = floor(map->p_pos.x / SCALE) * SCALE;
	if (cos(r_ang) > 0)
		map->p_pos.x_intercept_v += SCALE;
	map->p_pos.y_intercept_v = map->p_pos.y
		+ (map->p_pos.x_intercept_v - map->p_pos.x) * tan(r_ang);
}

void	calculate_vertical_steps(double r_ang, t_map *map)
{
	map->p_pos.x_step_v = SCALE;
	if (cos(r_ang) < 0)
		map->p_pos.x_step_v *= -1;
	map->p_pos.y_step_v = SCALE * tan(r_ang);
	if ((sin(r_ang) < 0 && map->p_pos.y_step_v > 0)
		|| (sin(r_ang) > 0 && map->p_pos.y_step_v < 0))
		map->p_pos.y_step_v *= -1;
}

bool	check_vertical_wall(t_map *map, float next_x,
	float next_y, double r_ang)
{
	int	map_x ;
	int	map_y ;

	map_x = floor(next_x / SCALE);
	if (cos(r_ang) < 0)
		map_x -= 1;
	map_y = floor(next_y / SCALE);
	if (map_x >= 0 && map_x < map->map_w && map_y >= 0
		&& map_y < map->map_h && map->map[map_y][map_x] == '1')
		return (true);
	return (false);
}

bool	check_and_update_vertical_intercept(t_map *map, double r_ang,
		t_pos *vert_inter)
{
	if (check_vertical_wall(map, map->p_pos.x_intercept_v,
			map->p_pos.y_intercept_v, r_ang))
	{
		vert_inter->x = map->p_pos.x_intercept_v;
		vert_inter->y = map->p_pos.y_intercept_v;
		return (true);
	}
	else
	{
		map->p_pos.x_intercept_v += map->p_pos.x_step_v;
		map->p_pos.y_intercept_v += map->p_pos.y_step_v;
		return (false);
	}
}

float	continue_vertical_intersection(t_map *map, double r_ang,
		t_pos *vert_inter)
{
	bool	hit_wall;
	float	vert_dist;

	hit_wall = false;
	vert_dist = INFINITY;
	while (!hit_wall && map->p_pos.x_intercept_v >= 0
		&& map->p_pos.x_intercept_v < map->map_w * SCALE
		&& map->p_pos.y_intercept_v >= 0
		&& map->p_pos.y_intercept_v < map->map_h * SCALE)
	{
		hit_wall = check_and_update_vertical_intercept(map, r_ang, vert_inter);
		if (hit_wall)
		{
			vert_dist = sqrt(pow(vert_inter->x - map->p_pos.x, 2)
					+ pow(vert_inter->y - map->p_pos.y, 2));
		}
	}
	return (vert_dist);
}
