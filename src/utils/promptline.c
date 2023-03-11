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

static char	*get_current_user(char *user)
{
	char	**username;
	char	*name;
	int		i;

	i = 0;
	username = ft_split(user, '/');
	while (username[i])
		i++;
	name = ft_strdup(username[i - 1]);
	free_split(username);
	return (name);
}

static char	*get_status_bar(void)
{
	char	*status;
	char	*tmp[5];
	char	*status_line;

	if (g_status == 0)
		return (NULL);
	status = ft_itoa(g_status);
	tmp[0] = ft_strjoin(KRED, " [");
	tmp[1] = ft_strjoin(tmp[0], status);
	tmp[2] = ft_strjoin(tmp[1], "]");
	status_line = ft_strjoin(tmp[2], KRST);
	free(status);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	return (status_line);
}

static void	free_tmp(char *tmp[7])
{
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp[3]);
	free(tmp[4]);
	free(tmp[5]);
	free(tmp[6]);
}

static void	get_prompt_line(t_msh *msh, char *user, char **promptline)
{
	char	*curdir;
	char	*tmp[7];
	char	*dir;
	char	*name;
	char	*status;

	name = get_current_user(user);
	tmp[0] = ft_strjoin(KGRN, name);
	free(name);
	tmp[1] = ft_strjoin(tmp[0], "\033[0m");
	curdir = get_currentdir(msh);
	tmp[2] = ft_strjoin(KGRN, curdir);
	free(curdir);
	tmp[3] = ft_strjoin(tmp[2], "\033[0m");
	tmp[4] = ft_strjoin("./", tmp[3]);
	dir = ft_strjoin("@minishell-4.2$ ", tmp[4]);
	status = get_status_bar();
	tmp[5] = ft_strjoin(dir, status);
	tmp[6] = ft_strjoin(tmp[5], " > ");
	*promptline = ft_strjoin(tmp[1], tmp[6]);
	free(dir);
	free(user);
	free(status);
	free_tmp(tmp);
}

void	build_promptline(char *user, char **promptline, t_msh *msh)
{
	if (user != NULL && ft_strlen(user) > 0)
		get_prompt_line(msh, user, promptline);
	else
	{
		get_prompt_line(msh, ft_strdup("user42"), promptline);
		if (user != NULL)
			free(user);
	}
}
