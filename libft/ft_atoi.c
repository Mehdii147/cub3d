/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:19:57 by ehafiane          #+#    #+#             */
/*   Updated: 2023/11/18 15:17:54 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handel(long int befor, long int after, int sign )
{
	if ((befor / 10) > after)
	{
		if (sign == 1)
			return (-1);
		return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long int	result;
	long int	befor;
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		befor = result * 10;
		result = (result * 10) + (str[i] - '0');
		if (handel(befor, result, sign) != 1)
			return (handel(befor, result, sign));
		i++;
	}
	return (result * sign);
}
