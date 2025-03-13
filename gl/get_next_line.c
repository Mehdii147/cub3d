/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:34:38 by mehdi             #+#    #+#             */
/*   Updated: 2023/12/16 14:19:21 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_stock(int fd, char *stock)
{
	char	*buff;
	int		readed;

	buff = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	readed = 1;
	while (!ft_strchr(stock, '\n') && readed != 0)
	{
		readed = read(fd, buff, BUFFER_SIZE);
		if (readed == -1)
			return (free(buff), free(stock), NULL);
		buff[readed] = '\0';
		stock = ft_strjoin(stock, buff);
	}
	free(buff);
	return (stock);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stock;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	stock = ft_read_stock(fd, stock);
	if (!stock)
		return (NULL);
	line = ft_get_line(stock);
	stock = new_stock(stock);
	return (line);
}
