/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 14:04:46 by dsy               #+#    #+#             */
/*   Updated: 2019/10/14 17:16:37 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s, const void *s2, size_t n)
{
	size_t				i;
	unsigned char		*dest;
	unsigned const char	*src;

	i = 0;
	dest = (unsigned char *)s;
	src = (unsigned const char *)s2;
	if (dest == src)
		return (0);
	while (i < (unsigned char)n)
	{
		if (dest[i] != src[i])
			return (dest[i] - src[i]);
		else
			i++;
	}
	return (0);
}
