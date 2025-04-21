/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horiz_cast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:16:50 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/21 14:25:25 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_horizontal_intercept(double r_ang, t_map *map)
{
	map->p_pos.y_intercept = floor(map->p_pos.y / SCALE) * SCALE;
	if (sin(r_ang) > 0)
		map->p_pos.y_intercept += SCALE;
	map->p_pos.x_intercept = map->p_pos.x
		+ (map->p_pos.y_intercept - map->p_pos.y) / tan(r_ang);
}

void	calculate_horizontal_steps(double r_ang, t_map *map)
{
	map->p_pos.y_step = SCALE;
	if (sin(r_ang) < 0)
		map->p_pos.y_step *= -1;
	map->p_pos.x_step = SCALE / tan(r_ang);
	if ((cos(r_ang) < 0 && map->p_pos.x_step > 0)
		|| (cos(r_ang) > 0 && map->p_pos.x_step < 0))
		map->p_pos.x_step *= -1;
}

bool	check_horizontal_wall(t_map *map, float next_x,
		float next_y, double r_ang)
{
	int	map_x ;
	int	map_y ;

	map_x = floor(next_x / SCALE);
	map_y = floor(next_y / SCALE);
	if (sin(r_ang) < 0)
		map_y -= 1;
	if (map_x >= 0 && map_x < map->map_w && map_y >= 0
		&& map_y < map->map_h && map->map[map_y][map_x] == '1')
		return (true);
	return (false);
}

bool	check_and_update_horizontal_intercept(t_map *map, double r_ang,
		t_pos *horz_inter)
{
	if (check_horizontal_wall(map, map->p_pos.x_intercept,
			map->p_pos.y_intercept, r_ang))
	{
		horz_inter->x = map->p_pos.x_intercept;
		horz_inter->y = map->p_pos.y_intercept;
		return (true);
	}
	else
	{
		map->p_pos.x_intercept += map->p_pos.x_step;
		map->p_pos.y_intercept += map->p_pos.y_step;
		return (false);
	}
}

float	continue_horizontal_intersection(t_map *map, double r_ang,
		t_pos *horz_inter)
{
	bool	hit_wall;
	float	horz_dist;

	hit_wall = false;
	horz_dist = INFINITY;
	while (!hit_wall && map->p_pos.x_intercept >= 0
		&& map->p_pos.x_intercept < map->map_w * SCALE
		&& map->p_pos.y_intercept >= 0
		&& map->p_pos.y_intercept < map->map_h * SCALE)
	{
		hit_wall = check_and_update_horizontal_intercept(map,
				r_ang, horz_inter);
		if (hit_wall)
		{
			horz_dist = sqrt(pow(horz_inter->x - map->p_pos.x, 2)
					+ pow(horz_inter->y - map->p_pos.y, 2));
		}
	}
	return (horz_dist);
}
