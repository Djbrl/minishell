/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:35:13 by jamrabhi          #+#    #+#             */
/*   Updated: 2023/01/14 22:35:15 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_quote(char *str, char **rt, int i)
{
	int		k;
	char	*tmp;

	if (str[i] == '\'' && str[i + 1])
	{
		i++;
		k = i;
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] && str[i] == '\'')
			i++;
		tmp = malloc(sizeof(char) * i - k + 1);
		ft_strlcpy(tmp, &str[k], i - k);
		add_to_rt(rt, tmp);
		free(tmp);
	}
	return (i);
}
