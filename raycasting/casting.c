/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 03:20:01 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/21 14:26:11 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	normalize_angle(double r_ang)
{
	while (r_ang < 0)
		r_ang += 2 * M_PI;
	while (r_ang >= 2 * M_PI)
		r_ang -= 2 * M_PI;
	return (r_ang);
}

t_pos	get_best_intersection(t_map *map, double r_ang)
{
	t_pos	intersection;
	t_pos	horz_inter;
	t_pos	vert_inter;

	r_ang = normalize_angle(r_ang);
	map->p_pos.horz_dist = find_horizontal_intersection(map, r_ang,
			&horz_inter);
	map->p_pos.vert_dist = find_vertical_intersection(map, r_ang, &vert_inter);
	if (map->p_pos.horz_dist < map->p_pos.vert_dist)
		intersection = horz_inter;
	else
		intersection = vert_inter;
	return (intersection);
}

void	process_ray(t_map *map, int column, double ray_angle)
{
	t_pos			horz_inter;
	t_pos			vert_inter;
	t_pos			intersection;
	mlx_texture_t	*texture;

	map->p_pos.horz_dist = find_horizontal_intersection(map, ray_angle,
			&horz_inter);
	map->p_pos.vert_dist = find_vertical_intersection(map, ray_angle,
			&vert_inter);
	get_wall_hit_info(map, horz_inter, vert_inter, &intersection);
	calculate_wall_dimensions(map, ray_angle, map->p_pos.ang);
	texture = select_texture(map, ray_angle);
	draw_wall_strip(map, column, texture,
		calculate_texture_x(map, intersection, texture));
	draw_ceiling(map, column);
	draw_floor(map, column);
}

void	game_loop(void *param)
{
	static double	last_time = 0;
	double			current_time ;
	t_map			*map;
	int				i;

	i = 0;
	map = (t_map *)param;
	current_time = mlx_get_time();
	clear_screen(map);
	move_player(map, current_time - last_time);
	last_time = current_time;
	while (i < W_WIDTH)
	{
		process_ray(map, i, calculate_ray_angle(map->p_pos.ang,
				FOV_R / W_WIDTH, i));
		i++;
	}
}
