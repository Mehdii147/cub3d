/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:37:40 by mehdi             #+#    #+#             */
/*   Updated: 2023/12/16 14:06:19 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	while (s && *s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (!((char)c))
		return (s);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*join;

	i = 0;
	j = 0;
	join = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!join)
		return (NULL);
	while (s1 && s1[j])
	{
		join[i++] = s1[j];
		j++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		join[i++] = s2[j];
		j++;
	}
	join[i] = '\0';
	free(s1);
	return (join);
}

char	*ft_get_line(char *stock)
{
	char	*str;
	int		i;

	i = 0;
	if (!stock[i])
		return (NULL);
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
		str = (char *)malloc(sizeof(char) * (i + 1));
	else
		str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (free(stock), NULL);
	i = -1;
	while (stock[++i] && stock[i] != '\n')
		str[i] = stock[i];
	if (stock[i] == '\n')
	{
		str[i] = stock[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*new_stock(char *stock)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
		return (free(stock), NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(stock) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (stock[i])
		str[j++] = stock[i++];
	str[j] = '\0';
	free(stock);
	return (str);
}
