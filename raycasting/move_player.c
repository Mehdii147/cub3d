/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:09:28 by ehafiane          #+#    #+#             */
/*   Updated: 2025/05/11 19:47:27 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	can_move_to(t_map *map, double new_x, double new_y, int walk_direction, int side_direction)
{
	if (map_has_wall_at(map, new_x, new_y))
		return (false);
	if (walk_direction != 0)
		if (!map_has_wall_at(map, new_x, map->p_pos.y))
			return (true);
	if (side_direction != 0)
		if (!map_has_wall_at(map, map->p_pos.x, new_y))
			return (true);
	return (!map_has_wall_at(map, new_x, new_y));
}

void	calculate_new_position(t_map *map, float delta_time,
		double *new_x, double *new_y)
{
	double	dx;
	double	dy;
	float	move_step;

	dx = 0;
	dy = 0;
	if (map->p_pos.walk_direction != 0)
	{
		move_step = map->p_pos.walk_direction * SPEED * delta_time;
		dx += cos(map->p_pos.ang) * move_step;
		dy += sin(map->p_pos.ang) * move_step;
	}
	if (map->p_pos.side_direction != 0)
	{
		move_step = map->p_pos.side_direction * SPEED * delta_time;
		dx += cos(map->p_pos.ang + M_PI_2) * move_step;
		dy += sin(map->p_pos.ang + M_PI_2) * move_step;
	}
	*new_x = map->p_pos.x + dx;
	*new_y = map->p_pos.y + dy;
}

void	move_player(t_map *map, float delta_time)
{
	double	new_x;
	double	new_y;

	map->p_pos.ang += map->p_pos.rotate_direction * ROTATE * delta_time;
	map->p_pos.ang = normalize_angle(map->p_pos.ang);
	calculate_new_position(map, delta_time, &new_x, &new_y);
	
	if (can_move_to(map, new_x, map->p_pos.y, map->p_pos.walk_direction, 0))
			map->p_pos.x = new_x;
	if (can_move_to(map, map->p_pos.x, new_y, 0, map->p_pos.side_direction))
			map->p_pos.y = new_y;
}

void	handle_movement_keys(mlx_key_data_t keydata, t_map *map)
{
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		map->p_pos.walk_direction = 1;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		map->p_pos.walk_direction = -1;
	else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_S)
		&& keydata.action == MLX_RELEASE)
		map->p_pos.walk_direction = 0;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		map->p_pos.side_direction = 1;
	else if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		map->p_pos.side_direction = -1;
	else if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
		&& keydata.action == MLX_RELEASE)
		map->p_pos.side_direction = 0;
}

void	handle_rotation_keys(mlx_key_data_t keydata, t_map *map)
{
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		map->p_pos.rotate_direction = 1;
	else if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		map->p_pos.rotate_direction = -1;
	else if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
		&& keydata.action == MLX_RELEASE)
		map->p_pos.rotate_direction = 0;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	handle_movement_keys(keydata, map);
	handle_rotation_keys(keydata, map);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		printf("Exiting...\n");
		mlx_close_window(map->mlx);
	}
}
