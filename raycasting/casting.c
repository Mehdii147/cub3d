/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 03:20:01 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/21 11:08:48 by ehafiane         ###   ########.fr       */
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
	mlx_texture_t 	*texture;
	double 			fov;

	fov = 60 * (M_PI / 180);
	map->p_pos.horz_dist = find_horizontal_intersection(map, ray_angle,
			&horz_inter);
	map->p_pos.vert_dist = find_vertical_intersection(map, ray_angle,
			&vert_inter);
	get_wall_hit_info(map, horz_inter, vert_inter, &intersection);
	calculate_wall_dimensions(map, ray_angle, map->p_pos.ang, fov);
	texture = select_texture(map, ray_angle);
	draw_wall_strip(map, column, texture,
		calculate_texture_x(map, intersection, texture));
	draw_ceiling(map, column);
	draw_floor(map, column);
}

void	game_loop(void *param)
{
	double			fov;
	int				num_rays;
	double			angle_increment;
	static double	last_time = 0;
	double			current_time ;
	double			delta_time ;
	t_map			*map;
	int				i;

	i = 0;
	map = (t_map *)param;
	current_time = mlx_get_time();
	delta_time = current_time - last_time;
	last_time = current_time;
	clear_screen(map);
	move_player(map, delta_time);
	init_ray_casting(&fov, &num_rays, &angle_increment);
	while (i < num_rays)
	{
		process_ray(map, i, calculate_ray_angle(map->p_pos.ang,
				fov, angle_increment, i));
		i++;
	}
}

