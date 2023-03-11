/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:40:28 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:28:50 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fail_command(char **expr)
{
	if (!is_redir(expr[0]))
		display_cmd_error(expr[0], CMD_ERROR, NULL);
	else
		display_cmd_error(expr[1], PATH_ERROR, NULL);
}

static void	exec_command(char *path, char *tmp, char **re, char **env)
{
	if (access(path, X_OK) == 0)
		execve(path, re, env);
	free(tmp);
	free(path);
}

static void	ftn_exec_paths(t_msh *msh, char **expr, char **re)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	if (access(expr[0], X_OK) == 0)
		execve(expr[0], re, msh->envp);
	reload_path(msh);
	while (msh->paths[i])
	{
		if (!ft_isalpha(expr[0][0]))
			break ;
		tmp = ft_strjoin(msh->paths[i++], "/");
		path = ft_strjoin(tmp, expr[0]);
		exec_command(path, tmp, re, msh->envp);
	}
}

static void	handle_builtin(int builtin, char *field, t_msh *msh)
{
	int	c;

	c = 0;
	if (builtin == 0 || builtin == 3 || builtin == 5)
	{
		c = exec_builtin(msh, field);
		temp_exit(msh);
		if (c == 0)
			exit(EXIT_SUCCESS);
		exit(-1);
	}
	else
	{
		temp_exit(msh);
		exit(0);
	}
}

void	exec_pipe_paths(t_msh *msh, char **re, char **cmd, char *field)
{
	char	**expr;
	int		builtin;

	builtin = 0;
	expr = remove_array_quotes(cmd);
	if (re == NULL)
		re = expr;
	builtin = is_builtin(expr[0], msh);
	if (builtin >= 0)
	{
		free_split(cmd);
		free_split(expr);
		handle_builtin(builtin, field, msh);
	}
	else
	{
		ftn_exec_paths(msh, expr, re);
		fail_command(expr);
	}
	free_split(expr);
}
