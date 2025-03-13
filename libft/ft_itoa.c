/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:35:39 by ehafiane          #+#    #+#             */
/*   Updated: 2023/11/17 11:04:26 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numb_alloc(int n)
{
	int	nb;

	nb = 0;
	if (n < 0)
	{
		nb++;
		n *= -1;
	}
	while (n != 0)
	{
		nb++;
		n = n / 10;
	}
	return (nb);
}

char	*ft_itoa(int n)
{
	char	*old;
	int		len;
	int		tmp;

	len = numb_alloc(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	old = malloc(sizeof(char) * len + 1);
	if (!old)
		return (NULL);
	old[len] = '\0';
	if (n < 0)
	{
		old[0] = '-';
		n *= -1;
	}
	while (n != 0)
	{
		tmp = n % 10 + 48;
		n /= 10;
		old[--len] = tmp;
	}
	return (old);
}
