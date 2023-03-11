/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 02:10:51 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:29:39 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (i < (int)ft_strlen(str))
	{
		if (str[i] != '"' && str[i] != '\'')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

void	copy_result(char **new_result, char **result, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new_result[i] = result[i];
		i++;
	}
}

char	**remove_array_quotes(char **cmd)
{
	int		i;
	int		j;
	char	*new_str;
	char	**result;
	char	**new_result;

	i = 0;
	j = 0;
	result = NULL;
	while (cmd[i])
	{
		new_result = malloc(sizeof(char *) * (j + 2));
		new_str = remove_quotes(cmd[i]);
		if (new_result == NULL)
			exit(EXIT_FAILURE);
		copy_result(new_result, result, j);
		new_result[j] = new_str;
		new_result[j + 1] = NULL;
		free(result);
		result = new_result;
		i++;
		j++;
	}
	return (result);
}

void	reload_path(t_msh *msh)
{
	char	**paths;
	char	*env_path;
	char	*name;

	name = ft_strdup("PATH");
	env_path = ft_strdup(get_data_from_env(msh->env, name));
	paths = ft_split(env_path, ':');
	if (!paths)
		return ;
	free_split(msh->paths);
	msh->paths = paths;
	free(env_path);
}

void	close_main_fork_process(t_msh *msh, int pid)
{
	waitpid(pid, &g_status, WUNTRACED);
	if (WIFSIGNALED(g_status) && WTERMSIG(g_status) == SIGINT)
	{
		update_exit_status(msh, 130);
		write(1, "\n", 1);
	}
	else
	{
		if (g_status > 130 && g_status != 256 && g_status != 512)
			g_status /= 256;
		update_exit_status(msh, g_status);
	}
}
