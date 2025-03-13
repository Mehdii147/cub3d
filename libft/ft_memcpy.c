/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:53:35 by ehafiane          #+#    #+#             */
/*   Updated: 2023/11/18 15:33:35 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*str; 
	unsigned char	*ptsrc;
	size_t			i;

	ptsrc = (unsigned char *)src;
	str = (unsigned char *)dst;
	i = 0;
	if (src == dst)
		return (0);
	while (i < n)
	{
		str[i] = ptsrc[i];
		i++;
	}
	return (dst);
}
