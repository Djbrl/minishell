/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:40:28 by dsy               #+#    #+#             */
/*   Updated: 2022/11/04 18:40:30 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_cmd(t_msh *msh, char **expr, int j)
{
	char	*cmd;
	char	*path;
	int		status;

	status = 0;
	if (access(expr[0], X_OK & F_OK) == 0)
		execve(expr[0], expr, msh->envp);
	cmd = ft_strjoin(msh->paths[j], "/");
	path = ft_strjoin(cmd, expr[0]);
	status = execve(path, expr, msh->envp);
	free(cmd);
	free(path);
	return (status);
}

static void	pipe_fork(t_msh *msh, char **expr, int fd[2], int j, int in, int out)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], out);
		while (msh->paths[j])
			pipe_cmd(msh, expr, j++);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], in);
		waitpid(pid, &g_status, WUNTRACED);
		while (!WIFEXITED(g_status) && !WIFSIGNALED(g_status))
			waitpid(pid, &g_status, WUNTRACED);
	}
}

int	pipe_exec(t_msh *msh)
{
	char	**expr;
	int		fd[2];
	int		i;
	int		j;

	i = 0;
	j = 0;
	pipe(fd);
	while (msh->expr[i])
	{
		expr = ft_split(msh->expr[i], ' ');
		pipe_fork(msh, expr, fd, j, 0, 1);
		close(fd[0]);
		close(fd[1]);
		// free_split(expr);
		j = 0;
		i++;
	}
	return (0);
}
