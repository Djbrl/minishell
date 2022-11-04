/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:59:40 by dsy               #+#    #+#             */
/*   Updated: 2022/04/05 16:29:34 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	isinset(char const str, char const *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (str == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	findsubstr(char const *s1, char const *set)
{
	int	i;
	int	y;

	i = ft_strlen(s1);
	y = 0;
	i--;
	while (i && isinset(s1[i], set))
	{
		i--;
		y++;
	}
	return (y);
}

char	*copysubstr(int d, int x, char *str, char const *s1)
{
	int	i;

	i = 0;
	while (d--)
	{
		str[i] = s1[i + x];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	x;
	int		d;

	x = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[x] && isinset(s1[x], set))
		x++;
	if (x == ft_strlen(s1))
	{
		str = malloc(sizeof(char) * 1);
		if (str == NULL)
			return (0);
		str[0] = '\0';
		return (str);
	}
	d = ft_strlen(s1) - findsubstr(s1, set) - x;
	str = malloc(sizeof(char) * d + 1);
	if (str == NULL)
		return (0);
	str = copysubstr(d, x, str, s1);
	return (str);
}
