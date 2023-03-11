/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:40:28 by dsy               #+#    #+#             */
/*   Updated: 2023/01/28 03:15:19 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_quote(char *str)
{
	int	i;
	int	q;

	q = 0;
	i = 0;
	while (str[i] && (str[i] != '>' || str[i] != '<'))
	{
		if (str[i] == '\"' || str[i] == '\'')
			q++;
		i++;
	}
	if ((q % 2) != 0)
		return (1);
	return (0);
}

int	check_quotes(char **redir, int *i)
{
	int	j;
	int	quotes;

	quotes = 0;
	j = *i;
	while (j > 0)
	{
		if (has_quote(redir[j]))
			quotes++;
		j--;
	}
	return (quotes);
}

static int	is_heredoc(char *token, char **redirs)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = ft_split_charset(token, "<<");
	while (tmp[i])
		i++;
	free_split(tmp);
	if (i > 1)
	{
		while (token[j + 1])
		{
			if (token[j] == '<' && (token[j + 1] == '<'))
			{
				free_split(redirs);
				return (1);
			}
			j++;
		}
	}
	return (0);
}

static int	has_no_redir(char *expr)
{
	int	i;
	int	red;

	red = 0;
	i = 0;
	while (expr[i])
	{
		if (expr[i] == '>' || expr[i] == '<')
			red = 1;
		i++;
	}
	if (red == 1)
		return (0);
	return (1);
}

void	apply_redirections(char *expr, int *fd_in, int *fd_out, t_msh *msh)
{
	int		i;
	char	**redirs;
	int		*fds[2];
	int		quotes;

	i = 0;
	if (has_no_redir(expr))
		return ;
	fds[0] = fd_in;
	fds[1] = fd_out;
	quotes = 0;
	redirs = ft_split(expr, ' ');
	while (redirs[i])
	{
		quotes = check_quotes(redirs, &i);
		if (is_redir_token(redirs[i], redirs) && (quotes % 2 == 0))
			handle_redir(expr, fds, &i, msh);
		else
		{
			is_heredoc(redirs[i], redirs);
			is_sneaky_token(expr, &i, fds, msh);
		}
		i++;
	}
	free_split(redirs);
}
