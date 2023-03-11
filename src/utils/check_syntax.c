/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_expand_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:17:24 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:29:53 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_unexpected_token(char *token)
{
	int	len;

	len = ft_strlen(token);
	if ((len == 1 && (token[0] == '>' || token[0] == '<' || token[0] == '|')) \
			|| (len == 2 && (ft_strcmp(token, ">>") == 0 \
					|| ft_strcmp(token, "<<") == 0)))
		return (1);
	return (0);
}

static int	is_token_at_end(char **res, int i)
{
	if (res[i + 1] == NULL)
		return (1);
	if (i == 0 && ft_strlen(res[i]) == 2 && ft_strcmp(res[i], "<<") == 0)
		return (1);
	return (0);
}

int	has_unexpected_token(char *str)
{
	char	**res;
	int		i;

	res = ft_split(str, ' ');
	i = 0;
	while (res[i])
	{
		if (is_unexpected_token(res[i]) && is_token_at_end(res, i))
		{
			free_split(res);
			return (1);
		}
		i++;
	}
	free_split(res);
	return (0);
}
