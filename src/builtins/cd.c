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

/*
** create error cd. The directory "[name]" does not exist
** if mhs->home NULL : bash: cd: HOME not set
*/

static int	ftn_msh_cd(t_msh **msh, int ret, char *field)
{
	char	**tokens;
	int		free_tokens;

	free_tokens = 0;
	if (field == NULL)
		tokens = (*msh)->tokens;
	else
	{
		tokens = ft_split(field, ' ');
		free_tokens = 1;
	}
	ret = change_dir(msh, tokens);
	if (free_tokens)
		free_split(tokens);
	return (ret);
}

/*
****************************STATIC FUNCTIONS****************************
*/

char	*get_currentdir(t_msh *msh)
{
	char	*path;
	char	*ret;
	char	cwd[1024];
	int		i;
	int		last_slash;

	i = -1;
	last_slash = 0;
	path = ft_strdup(getcwd(cwd, sizeof(cwd)));
	if (!path)
	{
		display_error(CWD_ERROR, msh);
		return (NULL);
	}
	if (ft_strlen(path) == 0)
	{
		free(path);
		return (ft_strdup(" "));
	}
	while (path[++i])
		if (path[i] == '/')
			last_slash = i;
	ret = ft_strdup(path + last_slash + 1);
	free(path);
	return (ret);
}

/*
**only if FIELD != NULL, also change it in echo
*/
int	msh_cd_runner(t_env_var *env, t_msh *msh, char *field)
{
	(void)msh;
	if (msh->nb_tokens > 2)
	{
		display_error(CD_ARG_ERROR, msh);
		exit_cmd(msh);
		return (update_exit_status(msh, 1));
	}
	else
		return (update_exit_status(msh, msh_cd(env, msh, field)));
}

int	msh_cd(t_env_var *env, t_msh *msh, char *field)
{
	int		ret;

	(void)env;
	ret = 0;
	ret = ftn_msh_cd(&msh, ret, field);
	if (ret < 0)
	{
		display_cmd_error("cd", PATH_ERROR, msh->tokens);
		exit_cmd(msh);
		return (1);
	}
	exit_cmd(msh);
	return (ret);
}
