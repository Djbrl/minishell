/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 19:44:55 by jamrabhi          #+#    #+#             */
/*   Updated: 2023/01/12 19:44:58 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_realloc(void *ptr, size_t cursize, size_t newsize)
{
	char	*newptr;

	if (!ptr)
	{
		newptr = (malloc(newsize));
		if (!newptr)
			return (NULL);
	}
	else
	{
		if (newsize <= cursize)
			return (ptr);
		newptr = malloc(newsize);
		if (!newptr)
			return (NULL);
		ft_memcpy(newptr, ptr, cursize);
		free(ptr);
	}
	return (newptr);
}
