/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:10:36 by amandour          #+#    #+#             */
/*   Updated: 2025/04/22 20:35:08 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "../inc/cub3d.h"

void	exact_angle(t_data *data, int i, int j, double *angle)
{
	if (data->map[i][j] == 'N')
		*angle = 3 * M_PI / 2;
	else if (data->map[i][j] == 'S')
		*angle = M_PI / 2;
	else if (data->map[i][j] == 'W')
		*angle = M_PI;
	else if (data->map[i][j] == 'E')
		*angle = 0.0;
}

double	update_angle(t_data *data)
{
	double		angle;
	int			i;
	int			j;

	i = 0;
	angle = 0.0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' \
				|| data->map[i][j] == 'W' || data->map[i][j] == 'E')
				exact_angle(data, i, j, &angle);
			j++;
		}
		i++;
	}
	return (angle);
}

void	initialize_position(t_data *data, double *x, double *y)
{
	int		j;
	size_t	i;

	j = 0;
	while (j < data->height)
	{
		i = 0;
		while (i < data->width)
		{
			if (data->map[j][i] == 'N' || data->map[j][i] == 'S'
			|| data->map[j][i] == 'W' || data->map[j][i] == 'E')
			{
				*x = i * SCALE + SCALE / 2;
				*y = j * SCALE + SCALE / 2;
				return ;
			}
			i++;
		}
		j++;
	}
}

t_data	*ft_parsing(char **av)
{
	t_data	*args;
	char	**file;
	int		i;

	args = mohi_bel_malloc(sizeof(t_data));
	i = 0;
	check_file_isvalid(av[1]);
	file = ft_read_map(av[1]);
	if (!file[0])
		ft_error_message("Error:\nempty map!!");
	init_data(args);
	get_data(args, file, &i);
	check_params(*args);
	check_map(file + i, args);
	check_map_round_byones(args);
	check_elements(args);
	rep_spaseses_to_ones(args);
	return (args);
}
