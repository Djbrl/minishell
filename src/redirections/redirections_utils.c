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

int	which_redir(char *redir, char *which, char dir, int mode)
{
	if (mode == 1)
		if (ft_strncmp(redir, which, ft_strlen(which)) == 0 || \
			((ft_strlen(redir) >= 2 && redir[ft_strlen(redir) - 2] == dir) && \
			(ft_strlen(redir) >= 1 && redir[ft_strlen(redir) - 1] == dir)))
			return (1);
	if (mode == 2)
		if (ft_strncmp(redir, which, ft_strlen(which)) == 0 || \
			(ft_strlen(redir) >= 1 && redir[ft_strlen(redir) - 1] == dir))
			return (1);
	if (mode == 3)
		if (ft_strncmp(redir, which, ft_strlen(which)) == 0 || \
			((ft_strlen(redir) >= 2 && redir[ft_strlen(redir) - 2] == dir) && \
			(ft_strlen(redir) >= 1 && redir[ft_strlen(redir) - 1] == dir)))
			return (1);
	if (mode == 4)
		if (ft_strncmp(redir, which, ft_strlen(which)) == 0 || \
			(ft_strlen(redir) >= 1 && redir[ft_strlen(redir) - 1] == dir))
			return (1);
	return (0);
}

static int	check_rkey(char tmp[HEREDOC_BUF_SIZE], char *field, \
	char *heredoc_buf[HEREDOC_BUF_SIZE], int i)
{
	char	**token;
	char	*rkey;
	char	**remove_q;

	token = ft_split(field, ' ');
	rkey = remove_spaces(token[0]);
	remove_q = ft_split_charset(rkey, "\"\'");
	free(rkey);
	free_split(token);
	if (ft_strncmp(tmp, remove_q[0], ft_strlen(remove_q[0])) == 0 \
		&& ft_strlen(tmp) == ft_strlen(remove_q[0]))
	{
		free(heredoc_buf[i]);
		free_split(remove_q);
		return (1);
	}
	free_split(remove_q);
	return (0);
}

static void	get_heredoc_lines(char *field, \
	char *heredoc_buf[HEREDOC_LIMIT], t_msh *msh)
{
	char	tmp[HEREDOC_BUF_SIZE];
	int		i;
	int		ret;

	i = 0;
	while (i < HEREDOC_LIMIT - 1)
	{
		write(1, "> ", 2);
		ret = read(0, tmp, HEREDOC_BUF_SIZE - 1);
		if (ret <= 0)
			break ;
		tmp[ret - 1] = '\0';
		if (ret == 1 || ret == 0)
			heredoc_buf[i] = ft_strdup("");
		else
			heredoc_buf[i] = heredoc_expand(tmp, msh);
		if (check_rkey(tmp, field, heredoc_buf, i))
			break ;
		ft_memset(tmp, 0, HEREDOC_BUF_SIZE);
		i++;
	}
	heredoc_buf[i] = NULL;
}

void	heredoc(char **field, t_msh *msh)
{
	char	*heredoc_buf[HEREDOC_LIMIT];
	char	*tmp;
	int		i;

	i = 0;
	while (i < HEREDOC_LIMIT)
		heredoc_buf[i++] = NULL;
	if (field[1])
		get_heredoc_lines(field[1], heredoc_buf, msh);
	else
		get_heredoc_lines(field[0], heredoc_buf, msh);
	tmp = ft_strdup(field[0]);
	free_split(field);
	ftn_heredoc(tmp, heredoc_buf, msh);
}
