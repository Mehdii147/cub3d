/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:07:02 by mehdi             #+#    #+#             */
/*   Updated: 2023/11/12 21:46:37 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*join;

	i = 0;
	j = 0;
	join = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!join)
		return (0);
	while (s1[j])
	{
		join[i++] = s1[j];
		j++;
	}
	j = 0;
	while (s2[j])
	{
		join[i++] = s2[j];
		j++; 
	}
	join[i] = '\0';
	return (join);
}
