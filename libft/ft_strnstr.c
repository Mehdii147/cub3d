/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:26:26 by ehafiane          #+#    #+#             */
/*   Updated: 2023/11/09 16:52:51 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!needle[0])
		return ((char *)haystack);
	if (!len)
		return (NULL);
	while (haystack[i] && len > i)
	{
		j = 0;
		while (needle[j] && (haystack[i + j] == needle[j]) && (i + j) < len)
		{
			j++;
		}
		if (!needle[j])
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
