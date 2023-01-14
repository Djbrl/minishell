/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:40:28 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:29:08 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	output_redirection(char **field, int mode, int *fd_out)
{
	int		j;
	int		fd;
	char	**expr;

	j = 1;
	fd = -1;
	while (field[j])
	{
		expr = ft_split(field[j], ' ');
		if (mode == 1)
			fd = open(expr[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (mode == 2)
			fd = open(expr[0], O_RDWR | O_CREAT | O_APPEND, 0644);
		free_split(expr);
		j++;
	}
	*fd_out = fd;
	free_split(field);
}

static void	heredoc(char *expr)
{
	char	*tmp;

	tmp = NULL;
	while (1)
	{
		get_next_line(0, &tmp);
		if (ft_strncmp(tmp, expr, ft_strlen(tmp)) == 0)
			break ;
		free(tmp);
	}
}

static void	check_paths(char *prompt)
{
	char	**redir;
	char	*expr;
	int		i;

	i = 1;
	redir = ft_split_charset(prompt, "<>");
	while (redir[i])
	{
		expr = remove_spaces(redir[i]);
		if (access(expr, F_OK) == -1)
		{
			display_cmd_error(redir[i], PATH_ERROR, NULL);
			free(expr);
			free_split(redir);
			exit(EXIT_FAILURE);
		}
		free(expr);
		i++;
	}
	free_split(redir);
}

static void	input_redirection(char **field, int mode, int *fd_in, char *prompt)
{
	int		j;
	int		fd;
	char	**expr;

	j = 1;
	fd = -1;
	check_paths(prompt);
	while (field[j])
	{
		expr = ft_split(field[j], ' ');
		if (mode == 1)
			fd = open(expr[0], O_RDONLY);
		if (mode == 2)
			heredoc(expr[0]);
		free_split(expr);
		j++;
	}
	*fd_in = fd;
	free_split(field);
}

void	apply_redirections(char *expr, int *fd_in, int *fd_out)
{
	int		i;
	char	**redirs;

	i = 0;
	(void)redirs;
	redirs = ft_split(expr, ' ');
	while (redirs[i])
	{
		if (ft_strncmp(redirs[i], ">>", ft_strlen(">>")) == 0)
			output_redirection(ft_split_charset(expr, ">"), 2, fd_out);
		else if (ft_strncmp(redirs[i], ">", ft_strlen(">")) == 0)
			output_redirection(ft_split_charset(expr, ">"), 1, fd_out);
		else if (ft_strncmp(redirs[i], "<<", ft_strlen("<<")) == 0)
			input_redirection(ft_split_charset(expr, "<<"), 2, fd_in, expr);
		else if (ft_strncmp(redirs[i], "<", ft_strlen("<")) == 0)
			input_redirection(ft_split_charset(expr, "<"), 1, fd_in, expr);
		else
			(void)redirs;
		i++;
	}
	free_split(redirs);
}
