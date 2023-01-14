/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:34:50 by jamrabhi          #+#    #+#             */
/*   Updated: 2023/01/14 22:34:53 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dollar_inside_dquote(char *str, char **rt, int i, t_msh *msh)
{
	char	*tmp;

	i++;
	tmp = malloc(sizeof(char) * i + 1);
	ft_strlcpy(tmp, str, i);
	add_to_rt(rt, tmp);
	free(tmp);
	i = dollar(str, rt, i, msh);
	return (i);
}

int	double_quote(char *str, char **rt, int i, t_msh *msh)
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
		add_to_rt(rt, tmp);
		free(tmp);
	}
	return (i);
}
