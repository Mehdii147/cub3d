/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:48:20 by ehafiane          #+#    #+#             */
/*   Updated: 2023/11/09 16:52:08 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*ret;
	int			len;

	len = ft_strlen(s);
	ret = (s + len);
	while (len >= 0)
	{
		if (*ret == (char)c)
			return ((char *)ret);
		ret--;
		len--;
	}
	if (!((char)c))
		return ((char *)s);
	return (0);
}
