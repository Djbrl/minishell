/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:54:14 by dsy               #+#    #+#             */
/*   Updated: 2022/04/05 16:27:29 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int n)
{
	int		i;

	i = ft_strlen(str) - 1;
	if (n == 0)
		i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == n)
			return ((char *)str + i);
		i--;
	}
	if (i == -1)
		return ((char *) NULL);
	return (0);
}
