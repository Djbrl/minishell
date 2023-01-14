/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <dsy@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:19:12 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:27:15 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
****************************STATIC FUNCTIONS****************************
*/

static int	ftn_msh_cd(t_msh **msh, char **path, int ret)
{
	char	*p;
	t_msh	*m;

	m = *msh;
	p = *path;
	if (m->tokens[1])
	{
		if (m->tokens[1][0] == '$')
			p = expand_var(m, m->tokens[1]);
		else
			p = ft_strdup(m->tokens[1]);
	}
	if (!m->tokens[1])
	{
		if (m->home != NULL)
			ret = chdir(m->home);
		else
			ret = chdir("/");
	}
	else
		ret = chdir(p);
	free(p);
	return (ret);
}

/*
****************************STATIC FUNCTIONS****************************
*/

char	*get_currentdir(t_msh *msh)
{
	char	*path;
	char	cwd[1024];
	int		i;
	int		last_slash;

	i = 0;
	last_slash = 0;
	path = ft_strdup(getcwd(cwd, sizeof(cwd)));
	if (!path)
	{
		display_error(CWD_ERROR, msh);
		return (NULL);
	}
	while (path[i])
	{
		if (path[i] == '/')
			last_slash = i;
		i++;
	}
	free(path);
	return (ft_strdup(path + last_slash + 1));
}

int	msh_cd_runner(t_env_var *env, t_msh *msh)
{
	(void)msh;
	if (msh->nb_tokens > 2)
	{
		display_error(CD_ARG_ERROR, msh);
		exit_cmd(msh);
		return (update_exit_status(msh, 1));
	}
	else
		return (update_exit_status(msh, msh_cd(env, msh)));
}

int	msh_cd(t_env_var *env, t_msh *msh)
{
	int		ret;
	char	*path;

	(void)env;
	ret = 0;
	path = NULL;
	ret = ftn_msh_cd(&msh, &path, ret);
	if (ret < 0)
	{
		display_cmd_error("cd", PATH_ERROR, msh->tokens);
		exit_cmd(msh);
		return (1);
	}
	exit_cmd(msh);
	return (0);
}
