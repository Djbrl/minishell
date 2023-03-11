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

void	output_redirection(char **field, int mode, int *fd_out)
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

void	input_redirection(char **field, int *fd_in, \
	char *prompt, t_msh *msh)
{
	int		j;
	int		fd;
	char	**expr;

	(void)msh;
	j = 1;
	fd = -1;
	(void)prompt;
	while (field[j])
	{
		expr = ft_split(field[j], ' ');
		fd = open(expr[0], O_RDONLY);
		free_split(expr);
		j++;
	}
	*fd_in = fd;
	free_split(field);
}

void	heredoc_redirection(char **redirs, char **field, t_msh *msh)
{
	free_split(redirs);
	heredoc(field, msh);
	free_split(field);
}

int	sneaky_redir(char *expr)
{
	int	i;

	i = 0;
	if (ft_strlen(expr) < 3)
		return (0);
	while (expr[i])
	{
		if (expr[i] == '>' && (expr[i + 1] != '>' || expr[i + 1] == 0))
			return (1);
		if (expr[i] == '<' && expr[i + 1] != '<')
			return (4);
		if (expr[i] == '>' && expr[i + 1] == '>' && expr[i + 2] != '>')
			return (2);
		if (expr[i] == '<' && expr[i + 1] == '<' && expr[i + 2] != '<')
			return (3);
		i++;
	}
	return (0);
}
