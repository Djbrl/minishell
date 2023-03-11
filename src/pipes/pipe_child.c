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

static void	check_paths(t_msh *msh, char **cmd, int redir, char *field)
{
	char	**res;
	char	**re;

	if (redir == 0)
		exec_pipe_paths(msh, NULL, cmd, field);
	else
	{
		res = ft_split_charset(field, "<>");
		re = ft_split(res[0], ' ');
		free_split(res);
		exec_pipe_paths(msh, re, cmd, field);
		free_split(re);
	}
}

static void	dup_command(t_expr **commands)
{
	t_expr	*cur;

	cur = *commands;
	if (cur->fd_out != 1)
	{
		dup2(cur->fd_out, 1);
		close(cur->fd_out);
	}
	if (cur->fd_in != 0)
	{
		dup2(cur->fd_in, 0);
		close(cur->fd_in);
	}
}

static void	execute_commands(t_expr **curr_command, t_msh *msh)
{
	t_expr	*cur;
	char	**cmd;
	int		i;
	int		redir;

	i = 0;
	redir = 0;
	cur = *curr_command;
	while (msh->tokens[i])
	{
		if ((msh->tokens[i][0] == '>' || msh->tokens[i][0] == '<') \
		&& ft_strlen(msh->tokens[i]) < 3)
		{
			apply_redirections(cur->data, &cur->fd_in, &cur->fd_out, msh);
			redir = 1;
			break ;
		}
		i++;
	}
	dup_command(curr_command);
	cmd = ft_split(cur->data, ' ');
	check_paths(msh, cmd, redir, cur->data);
	free_split(cmd);
}

void	child_pipe(t_expr *curr, t_msh *msh)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execute_commands(&curr, msh);
	temp_exit(msh);
	exit(EXIT_FAILURE);
}
