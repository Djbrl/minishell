/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 03:15:12 by dsy               #+#    #+#             */
/*   Updated: 2022/10/13 12:24:06 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_env(t_msh *msh)
{
	int		i;
	char	*cmd;
	char	*path;
	int		status;

	i = 0;
	status = access(msh->tokens[0], X_OK & F_OK);
	if (!msh->paths)
		return (-1);
	if (msh->expr == NULL)
	{
		while (msh->paths[i])
		{
			if (status == 0)
				execve(msh->tokens[0], msh->tokens, msh->envp);
			cmd = ft_strjoin(msh->paths[i++], "/");
			path = ft_strjoin(cmd, msh->tokens[0]);
			execve(path, msh->tokens, msh->envp);
			free(cmd);
			free(path);
		}
	}
	else
		status = pipe_exec(msh);
	return (status);
}

void	signal_handler(int sig_n)
{
	if (sig_n == SIGINT)
	{
		write(1, "\n", 1);
		write(1, PROMPTLINE, ft_strlen(PROMPTLINE));
	}
	else
		return ;
}

void	evaluate_commands(t_msh *msh)
{
	pid_t	pid;

	if (is_builtin(msh->tokens[0], msh) >= 0)
		msh->cmd.ptr[is_builtin(msh->tokens[0], msh)](msh->env, msh);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (exec_env(msh) == -1)
				display_error(CMD_ERROR, msh);
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
			display_error(FORK_ERROR, msh);
		else
		{
			waitpid(pid, &g_status, WUNTRACED);
			while (!WIFEXITED(g_status) && !WIFSIGNALED(g_status))
				waitpid(pid, &g_status, WUNTRACED);
			update_exit_status(msh, g_status);
		}
	}
}
