/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 22:17:23 by jamrabhi          #+#    #+#             */
/*   Updated: 2023/01/14 22:17:27 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_env(char *str, t_msh *msh)
{
	int		i;
	char	*tmp;
	char	*rt;

	i = 0;
	rt = NULL;
	while (str[i] && str[i] != '"' && str[i] != '\'' && !is_whitespace(str[i])
		&& !is_pipe_redir(str[i]))
		i++;
	tmp = malloc(sizeof(char) * i + 1);
	ft_strlcpy(tmp, str, i + 1);
	rt = get_data_from_env(msh->env, tmp);
	return (rt);
}

int	dollar(char *str, char **rt, int i, t_msh *msh)
{
	if (str[i] == '$')
		i++;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		add_to_rt(rt, expand_env(&str[i], msh));
		while (str[i] && str[i] != '"' && str[i] != '\''
			&& !is_whitespace(str[i]) && !is_pipe_redir(str[i]))
			i++;
	}
	else
		add_to_rt(rt, "$");
	return (i);
}
