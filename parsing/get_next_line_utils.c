/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandour <amandour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:07:03 by amandour          #+#    #+#             */
/*   Updated: 2025/04/07 18:11:49 by amandour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	result = (char *) mohi_bel_malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[i] != '\0')
		result[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		result[j++] = s2[i++];
	result[j] = '\0';
	return (result);
}

char	*ft_strdup(const char *src)
{
	char	*dst;
	size_t	len;
	size_t	i;

	len = ft_strlen(src);
	dst = mohi_bel_malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = (char *) mohi_bel_malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	rep_spaseses_to_ones(t_data *args)
{
	int	i;
	int	j;

	i = 0;
	while (args->map[i])
	{
		j = 0;
		while (args->map[i][j])
		{
			if (args->map[i][j] == ' ')
				args->map[i][j] = '1';
			j++;
		}
		i++;
	}
}
