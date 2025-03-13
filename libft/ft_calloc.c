/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:42:49 by ehafiane          #+#    #+#             */
/*   Updated: 2023/11/16 13:35:01 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*loc;

	loc = malloc(count * size);
	if (!loc)
		return (NULL);
	ft_bzero(loc, count * size);
	return (loc);
}
