/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_expand_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:17:24 by dsy               #+#    #+#             */
/*   Updated: 2023/02/15 17:26:34 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			return (1);
		i++;
	}
	return (0);
}

int	is_builtin(char *s, t_msh *msh)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (!ft_strncmp(msh->cmd.name[i], s, ft_strlen(msh->cmd.name[i]) + 1))
			return (i);
		i++;
	}
	return (-1);
}

static void	check_prompt(t_msh *msh, char *s)
{
	int	i;

	i = -1;
	if (ft_strlen(s) != 0)
		add_history(s);
	if (has_odd_quotes(s) || has_unexpected_token(s))
	{
		printf(SYNTAX_ERR_QUOTES);
		ft_memset(msh->g_buffer, 0, BUF);
		return ;
	}
	if (ft_strlen(s) == 0)
		ft_memset(msh->g_buffer, 0, BUF);
	else
	{
		while (s[++i] && s[i] != '\n')
			msh->g_buffer[i] = s[i];
	}
}

static void	exit_failure(t_msh *msh)
{
	(void)msh;
	ft_memset(msh->g_buffer, 0, BUF);
	free_env(msh);
	free_expr(&msh);
	exit(EXIT_SUCCESS);
}

void	read_buffer(t_msh *msh)
{
	char	*s;
	char	*user;
	char	*promptline;

	dup2(msh->std_in, 0);
	user = ft_strdup(get_data_from_env(msh->env, ft_strdup("USER")));
	promptline = NULL;
	build_promptline(user, &promptline, msh);
	s = readline(promptline);
	free(promptline);
	if (s != NULL)
		check_prompt(msh, s);
	else
		exit_failure(msh);
	if (g_status == CTRL_D_SIGNAL)
	{
		ft_memset(msh->g_buffer, 0, BUF);
		g_status = 0;
	}
	free(s);
}
