/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:23:11 by dsy               #+#    #+#             */
/*   Updated: 2022/04/05 16:26:14 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	size_t	i;
	char	*newstr;

	i = 0;
	if (n > ft_strlen(str))
		n = ft_strlen(str);
	newstr = (char *)malloc(sizeof(char) * n + 1);
	if (!newstr)
		return (NULL);
	while (i < n)
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
