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

/*reset FDs to standard on error
**fix display cmd format
**check exit status from forks
**handle multipie if builtin is first command
**handle heredoc
*/

static void	parent_status_check(t_msh *msh)
{
	if (g_status == 65280)
		update_exit_status(msh, 1);
	else
		update_exit_status(msh, g_status);
}

static void	check_pid_status(t_expr **cmd, t_msh *msh, int pid[100], int count)
{
	t_expr	*curr;
	int		j;

	curr = *cmd;
	if (curr->fd_in != STDIN_FILENO)
		close(curr->fd_in);
	if (curr->fd_out != STDOUT_FILENO)
		close(curr->fd_out);
	if (WIFSIGNALED(g_status) && WTERMSIG(g_status) == SIGINT)
	{
		update_exit_status(msh, 130);
		write(1, "\n", 1);
	}
	else
		update_exit_status(msh, g_status);
	if (curr->next == NULL)
	{
		j = 0;
		while (j < count + 1)
		{
			waitpid(pid[j], &g_status, WUNTRACED);
			parent_status_check(msh);
			j++;
		}
	}
}

static void	exit_fork(t_msh *msh)
{
	temp_exit(msh);
	exit(EXIT_FAILURE);
}

static int	execute_multi_pipe(t_expr *commands, t_msh *msh)
{
	t_expr	*curr;
	int		count;
	int		pid[100];

	count = 0;
	curr = commands;
	while (curr != NULL && count < 100)
	{
		pid[count] = fork();
		if (pid[count] == 0)
			child_pipe(curr, msh);
		else if (pid[count] < 0)
			exit_fork(msh);
		else
		{
			check_pid_status(&curr, msh, pid, count);
			count++;
			curr = curr->next;
		}
	}
	return (1);
}

int	pipe_exec(t_msh *msh)
{
	t_expr	*prev;
	t_expr	*commands;
	int		status;

	prev = NULL;
	commands = msh->exp->next;
	if (init_fds(&commands, prev) == -1)
		return (-1);
	status = execute_multi_pipe(commands, msh);
	return (status);
}
