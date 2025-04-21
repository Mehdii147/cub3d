/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:15:57 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/21 14:27:09 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	clear_screen(t_map *map)
{
	int	i;

	i = 0;
	while (i < W_WIDTH * W_HEIGHT)
	{
		mlx_put_pixel(map->img.img, i % W_WIDTH, i / W_WIDTH, 0x0FFFFF0F);
		i++;
	}
}

double	calculate_ray_angle(double player_angle,
		double angle_increment, int column)
{
	return (player_angle - (FOV_R / 2) + (column * angle_increment));
}

void	get_wall_hit_info(t_map *map, t_pos horz_inter,
		t_pos vert_inter, t_pos *intersection)
{
	map->p_pos.is_horz_hit = (map->p_pos.horz_dist < map->p_pos.vert_dist);
	if (map->p_pos.is_horz_hit)
	{
		*intersection = horz_inter;
		map->p_pos.distance = map->p_pos.horz_dist;
	}
	else
	{
		*intersection = vert_inter;
		map->p_pos.distance = map->p_pos.vert_dist;
	}
}

float	find_horizontal_intersection(t_map *map, double r_ang,
		t_pos *horz_inter)
{
	if (sin(r_ang) == 0)
		return (INFINITY);
	init_horizontal_intercept(r_ang, map);
	calculate_horizontal_steps(r_ang, map);
	return (continue_horizontal_intersection(map, r_ang, horz_inter));
}

float	find_vertical_intersection(t_map *map, double r_ang, t_pos *vert_inter)
{
	if (cos(r_ang) == 0)
		return (INFINITY);
	init_vertical_intercept(r_ang, map);
	calculate_vertical_steps(r_ang, map);
	return (continue_vertical_intersection(map, r_ang, vert_inter));
}
