/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:52:14 by dsy               #+#    #+#             */
/*   Updated: 2022/04/05 16:25:44 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*stock;
	unsigned int	i;

	if (!s)
		return (NULL);
	stock = ft_strdup(s);
	if (!stock)
		return (NULL);
	i = 0;
	while (stock[i])
	{
		stock[i] = f(i, stock[i]);
		i++;
	}
	return (stock);
}
