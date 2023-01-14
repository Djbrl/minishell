/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:11:20 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:28:17 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str || ft_strlen(str) == 0)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static void	parse_paths(char *path, t_msh *msh)
{
	char	**paths;

	paths = ft_split(path, ':');
	if (!paths)
		return ;
	else
		msh->paths = paths;
	return ;
}

void	parse_envp(t_msh *msh)
{
	int		i;
	char	*var;
	char	*data;

	i = 0;
	if (msh->envp == NULL)
		return ;
	while (msh->envp[i])
	{
		var = ft_substr(msh->envp[i], 0, find_char(msh->envp[i], '='));
		if (!var)
			return ;
		data = ft_substr(msh->envp[i], find_char(msh->envp[i], '=') + 1 \
			, find_char(msh->envp[i], '\0'));
		add_var_to_env(msh->env, var, data);
		if (ft_strncmp(var, "PATH", ft_strlen(var)) == 0)
			parse_paths(data, msh);
		if (ft_strncmp(var, "HOME", ft_strlen(var)) == 0)
			msh->home = ft_strdup(data);
		free(var);
		free(data);
		i++;
	}
	return ;
}
