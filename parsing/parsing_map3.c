/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:59:44 by amandour          #+#    #+#             */
/*   Updated: 2025/04/21 14:32:51 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	is_num(char *str)
{
	while (*str)
	{
		if (ft_atoi(str) < 0 || ft_atoi(str) > 255)
			ft_error_message("Error:\nInvalid color!!");
		str++;
	}
}

void	init_data(t_data *args)
{
	args->f_c = -1;
	args->c_color = -1;
	args->no = NULL;
	args->so = NULL;
	args->we = NULL;
	args->ea = NULL;
	args->map = NULL;
	args->height = 0;
	args->width = 0;
}

void	check_params(t_data args)
{
	if (!args.no || !args.so || !args.we || !args.ea)
		ft_error_message("Error:\nMissing texture!!");
	if (args.f_c == -1 || args.c_color == -1)
		ft_error_message("Error:\nMissing color!!");
}

static void	check_valid_map(t_data *args)
{
	int	i;
	int	j;

	1 && (i = 0, j = 0);
	while (args->map[i])
	{
		j = 0;
		while (args->map[i][j])
		{
			if (args->map[i][j] != '1' && args->map[i][j] != '0' \
				&& args->map[i][j] != 'N' \
				&& args->map[i][j] != 'S' && args->map[i][j] != 'W' \
				&& args->map[i][j] != 'E' && args->map[i][j] != ' ')
			{
				ft_error_message("Error:\nInvalid map!!7");
			}
			j++;
		}
		i++;
	}
}

void	check_elements(t_data *args)
{
	int	i;
	int	j;
	int	count;

	1 && (i = 0, count = 0, j = 0);
	while (args->map[i])
	{
		j = 0;
		while (args->map[i][j])
		{
			if (args->map[i][j] == 'N' || args->map[i][j] == 'S' \
				|| args->map[i][j] == 'W' || args->map[i][j] == 'E')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		ft_error_message("Error:\nInvalid number of players!!");
	check_valid_map(args);
}
