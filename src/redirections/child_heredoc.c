/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:40:28 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:29:14 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_heredoc(char *heredoc_buf[HEREDOC_LIMIT])
{
	int	i;

	i = 0;
	while (heredoc_buf[i] != NULL)
	{
		printf("%s\n", heredoc_buf[i]);
		free(heredoc_buf[i++]);
	}
}

static void	find_path(t_msh *msh, char **arg)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	while (msh->paths[i])
	{
		if (access(arg[0], X_OK) == 0)
			execve(arg[0], arg, msh->envp);
		tmp = ft_strjoin(msh->paths[i++], "/");
		path = ft_strjoin(tmp, arg[0]);
		if (access(path, X_OK) == 0)
			execve(path, arg, msh->envp);
		free(tmp);
		free(path);
	}
}

static void	exec_heredoc(t_msh *msh, char *cmd)
{
	char	**arg;

	arg = ft_split(cmd, ' ');
	free(cmd);
	if (arg[0] != NULL)
	{
		if (access(arg[0], X_OK) == 0)
			execve(arg[0], arg, msh->envp);
		find_path(msh, arg);
	}
	free_split(arg);
	temp_exit(msh);
	exit(EXIT_FAILURE);
}

static void	child_heredoc(int pipefd[2], char *buf[HEREDOC_LIMIT], \
	t_msh *msh, char *cmd)
{
	close(pipefd[0]);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	print_heredoc(buf);
	free(cmd);
	temp_exit(msh);
	exit(EXIT_SUCCESS);
}

void	ftn_heredoc(char *cmd, char *buf[HEREDOC_LIMIT], t_msh *msh)
{
	int		pipefd[2];
	int		pid;
	int		i;

	i = 0;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
		child_heredoc(pipefd, buf, msh, cmd);
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		waitpid(pid, &g_status, WUNTRACED);
		while (buf[i] != NULL)
			free(buf[i++]);
		exec_heredoc(msh, cmd);
	}
}
