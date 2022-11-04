/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:32:43 by dsy               #+#    #+#             */
/*   Updated: 2022/04/05 16:34:55 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, int len)
{
	int		i;
	char	*newstr;

	i = 0;
	if (!s || len < 0)
	{
		newstr = malloc(sizeof(char));
		if (!newstr)
			return (NULL);
		newstr[0] = 0;
		return (newstr);
	}
	newstr = (char *)malloc(sizeof(char) * len + 1);
	if (!newstr)
		return (NULL);
	if (start > ft_strlen(s))
	{
		newstr[0] = '\0';
		return (newstr);
	}
	while (i < len && s[start])
		newstr[i++] = s[start++];
	newstr[i] = '\0';
	return (newstr);
}
