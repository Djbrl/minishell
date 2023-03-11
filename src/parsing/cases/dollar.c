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
	return (ft_strdup(rt));
}

int	dollar(char *str, char **rt, int i, t_msh *msh)
{
	char	*tmp;

	if (str[i] == '$')
		i++;
	if (ft_isalpha(str[i]) || str[i] == '_' || str[i] == '?')
	{
		tmp = expand_env(&str[i], msh);
		add_to_rt(rt, tmp);
		free(tmp);
		while (str[i] && str[i] != '"' && str[i] != '\''
			&& !is_whitespace(str[i]) && !is_pipe_redir(str[i]))
			i++;
	}
	else
		add_to_rt(rt, "$");
	return (i);
}
