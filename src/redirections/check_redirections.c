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

int	is_redir_token(char *token, char **redirs)
{
	if (has_quote(token))
		return (0);
	if (which_redir(token, ">>", '>', 1))
		return (1);
	else if (which_redir(token, ">", '>', 2))
		return (1);
	else if (which_redir(token, "<<", '<', 3))
	{
		free_split(redirs);
		return (1);
	}
	else if (which_redir(token, "<", '<', 4))
		return (1);
	else
		return (0);
}

int	handle_redir(char *expr, int *fds[2], int *i, t_msh *msh)
{
	char	**redir;
	int		ret;

	ret = 0;
	redir = ft_split(expr, ' ');
	if (which_redir(redir[*i], ">>", '>', 1))
		output_redirection(ft_split_charset(expr, ">"), 2, fds[1]);
	else if (which_redir(redir[*i], ">", '>', 2))
		output_redirection(ft_split_charset(expr, ">"), 1, fds[1]);
	else if (which_redir(redir[*i], "<<", '<', 3))
		heredoc_redirection(redir, ft_split_charset(expr, "<<"), msh);
	else if (which_redir(redir[*i], "<", '<', 4))
		input_redirection(ft_split_charset(expr, "<"), fds[0], expr, msh);
	else
		ret = 1;
	free_split(redir);
	if (ret == 0)
		return (0);
	return (1);
}

int	is_sneaky_token(char *expr, int *i, int *fds[2], t_msh *msh)
{
	int		ret;
	char	**r;

	r = ft_split(expr, ' ');
	ret = sneaky_redir(r[*i]);
	if (ret != 0 && check_quotes(r, i) % 2 == 0)
	{
		if (ret == 1 && (r[*i][0] != '\"' || r[*i][0] != '\''))
			output_redirection(ft_split_charset(r[*i], ">"), 1, fds[1]);
		else if (ret == 2 && (r[*i][0] != '\"' || r[*i][0] != '\''))
			output_redirection(ft_split_charset(r[*i], ">"), 2, fds[1]);
		else if (ret == 3 && (r[*i][0] != '\"' || r[*i][0] != '\''))
			heredoc_redirection(r, ft_split_charset(r[*i], "<<"), msh);
		else if (ret == 4 && (r[*i][0] != '\"' || r[*i][0] != '\''))
			input_redirection(ft_split_charset(r[*i], "<"), fds[0], r[*i], msh);
		else
			ret = 0;
	}
	else
		ret = 0;
	free_split(r);
	if (ret == 0)
		return (0);
	return (1);
}

static void	dup_fds(int in, int out)
{
	if (in != -1)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != -1)
	{
		dup2(out, 1);
		close(out);
	}
}

int	check_redirections(t_msh *msh)
{
	int		in;
	int		out;
	int		i;
	int		redir;

	i = 0;
	in = -1;
	out = -1;
	redir = 0;
	while (msh->tokens[i])
	{
		if ((msh->tokens[i][0] == '>' || \
		msh->tokens[i][0] == '<') && ft_strlen(msh->tokens[i]) < 3)
		{
			apply_redirections(msh->prompt, &in, &out, msh);
			redir = 1;
			break ;
		}
		i++;
	}
	dup_fds(in, out);
	if (redir == 1)
		return (1);
	else
		return (0);
}
