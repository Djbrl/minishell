/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote_case.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:38:16 by jamrabhi          #+#    #+#             */
/*   Updated: 2023/01/12 21:38:17 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_quote_case(char *str, char **rt, int i, t_msh *msh)
{
	int		k;
	char	*tmp;

	tmp = ft_strdup("");
	if (str[i] == '\'' && str[i + 1])
	{
		i++;
		k = i;
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] && str[i] == '\'')
			i++;
		free(tmp);
		tmp = malloc(sizeof(char) * i - k + 1);
		ft_strlcpy(tmp, &str[k], i - k);
		replace_rt(rt, tmp);
	}
	free(tmp);
	return (i);
}
