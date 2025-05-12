/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mohilloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:10:49 by amandour          #+#    #+#             */
/*   Updated: 2025/05/12 20:17:10 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	clearheap(t_heap **node)
{
	t_heap	*tmp;

	if (!node || !*node)
		return ;
	tmp = *node;
	while (node && *node)
	{
		free(tmp->ptr);
		tmp->ptr = NULL;
		tmp = tmp->next;
		free(*node);
		*node = tmp;
	}
}

void	heap_addback(t_heap **lst, t_heap *new)
{
	t_heap	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_heap	*heap_new(void *content)
{
	t_heap	*head;

	head = (t_heap *)malloc(sizeof(t_heap));
	if (!head)
		return (NULL);
	head->ptr = content;
	head->next = NULL;
	return (head);
}

void	*mohi_bel_malloc(size_t __size)
{
	(void)__size;
	void	*__ptr;
	t_heap	*__node;
	t_cube	*__cub;

	__cub = (t_cube *)malloc(sizeof(t_cube));
	__ptr = malloc(__size);
	if (__ptr == NULL)
	{
		clearheap(&__cub->heap);
		ft_error_message("Error:\nmalloc failed");
	}
	__node = heap_new(__ptr);
	if (!__node)
	{
		free(__ptr);
		clearheap(&__cub->heap);
		ft_error_message("Error:\nmalloc failed");
	}
	heap_addback(&__cub->heap, __node);
	return (__ptr);
}
