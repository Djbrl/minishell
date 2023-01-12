/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_case.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:39:22 by jamrabhi          #+#    #+#             */
/*   Updated: 2023/01/12 21:39:24 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dollar_inside_dquote(char *str, char **rt, int i, t_msh *msh)
{
	char	*tmp;

	i++;
	tmp = malloc(sizeof(char) * i + 1);
	ft_strlcpy(tmp, str, i);
	replace_rt(rt, tmp);
	free(tmp);
	i = dollar_case(str, rt, i, msh);
	return (i);
}

int	double_quote_case(char *str, char **rt, int i, t_msh *msh)
{
	int		k;
	char	*tmp;

	if (str[i] == '\"' && str[i + 1])
	{
		i++;
		k = i;
		while (str[i] && (str[i] != '\"'))
		{
			if (str[i] == '$')
			{
				i = k + dollar_inside_dquote(&str[k], rt, i - k, msh);
				k = i;
			}
			else
				i++;
		}
		if (str[i] && str[i] == '\"')
			i++;
		tmp = malloc(sizeof(char) * i - k + 1);
		ft_strlcpy(tmp, &str[k], i - k);
		replace_rt(rt, tmp);
	}
	free(tmp);
	return (i);
}
