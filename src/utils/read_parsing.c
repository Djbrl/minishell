/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_expand_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:17:24 by dsy               #+#    #+#             */
/*   Updated: 2023/02/15 17:26:34 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(t_msh *msh, char *var)
{
	char	*ret;
	char	*find;

	find = ft_substr(var, 1, ft_strlen(var) - 1);
	ret = get_data_from_env(msh->env, find);
	if (ret == NULL)
		return (ft_strdup(var));
	else
		return (ft_strdup(ret));
}

int	has_odd_quotes(char *str)
{
	int	i;
	int	unclosed_q;
	int	unclosed_dq;
	int	unclosed;

	unclosed = 0;
	unclosed_q = 0;
	unclosed_dq = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			unclosed_q = 1;
		if (str[i] == '\"' && unclosed_q == 1)
			unclosed_q = 0;
		if (str[i] == '\'')
			unclosed_dq = 1;
		if (str[i] == '\'' && unclosed_dq == 1)
			unclosed_dq = 0;
		i++;
	}
	if (unclosed_q || unclosed_dq)
		unclosed = 1;
	return (unclosed);
}

static int	is_pipe_or_redir(char *str)
{
	int	len;

	if (str)
	{
		len = ft_strlen(str);
		if ((len == 1 && (str[0] == '>' || str[0] == '<' || str[0] == '|')) \
			|| (len == 2 && (ft_strcmp(str, ">>") == 0 \
			|| ft_strcmp(str, "<<") == 0)))
			return (1);
	}
	return (0);
}

static int	is_invalid_redir(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '>')
	{
		while (str[i] == '>' && str[i])
			i++;
		if (i > 2)
			return (1);
	}
	i = 0;
	if (str[0] == '<' && str[i])
	{
		while (str[i] == '<')
			i++;
		if (i > 2)
			return (1);
	}
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
		if (is_pipe_or_redir(res[i]))
		{
			if (res[i + 1] == NULL || is_pipe_or_redir(res[i + 1]))
			{
				free_split(res);
				return (1);
			}
		}
		else if ((i == 0 && ft_strlen(res[i]) == 2 && \
		!ft_strcmp(res[i], "<<")) || is_invalid_redir(res[i]))
		{
			free_split(res);
			return (1);
		}
		i++;
	}
	free_split(res);
	return (0);
}
