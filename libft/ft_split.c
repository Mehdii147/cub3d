/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:57:40 by ehafiane          #+#    #+#             */
/*   Updated: 2023/11/16 21:48:44 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	counter(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] != c && str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static char	*get_word( char const *str, char sep)
{
	char	*sub;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != sep)
		i++;
	sub = ft_substr(str, 0, i);
	if (!sub)
		return (NULL);
	return (sub);
}

static void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return ;
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		j;

	i = 0;
	j = 0;
	split = (char **)malloc(sizeof(char *) * (counter(s, c) + 1));
	if (!split)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != c && s[i])
		{
			split[j] = get_word(s + i, c);
			if (!split[j])
				return (ft_free(split), NULL);
			j++;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (split[j] = 0, split);
}
