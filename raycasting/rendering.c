/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:15:57 by ehafiane          #+#    #+#             */
/*   Updated: 2025/04/20 23:28:10 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_ray_casting(double *fov, int *num_rays, double *angle_increment)
{
	*fov = 60 * (M_PI / 180);
	*num_rays = W_WIDTH;
	*angle_increment = *fov / *num_rays;
}

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

double	calculate_ray_angle(double player_angle, double fov,
		double angle_increment, int column)
{
	return (player_angle - (fov / 2) + (column * angle_increment));
}

void	get_wall_hit_info(float horz_dist, float vert_dist, t_pos horz_inter, 
					 t_pos vert_inter, bool *is_horz_hit, t_pos *intersection, 
					 double *distance)
{
	*is_horz_hit = (horz_dist < vert_dist);
	if (*is_horz_hit)
	{
		*intersection = horz_inter;
		*distance = horz_dist;
	}
	else
	{
		*intersection = vert_inter;
		*distance = vert_dist;
	}
}
