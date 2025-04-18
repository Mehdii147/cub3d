/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandour <amandour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:02:52 by amandour          #+#    #+#             */
/*   Updated: 2025/04/10 21:05:50 by amandour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


int	main(int ac, char **av)
{
	t_cube		cube;


	if (ac != 2)
		ft_error_message("num of args isn't correct.Usage: ./cub3D <map_file>");
	get_cub(&cube);
	cube.data = ft_parsing(av);

}