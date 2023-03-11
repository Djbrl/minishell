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

static int	change_dir_helper(t_msh *msh, char *path)
{
	int		ret;
	char	cwd[1024];

	ret = chdir(path);
	if (ret == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			printf(CHDIR_ERR);
		else
			msh->last_valid_path = getcwd(cwd, sizeof(cwd));
	}
	free(path);
	return (ret);
}

static int	change_dir_default(t_msh *msh)
{
	int	ret;

	if (msh->home != NULL)
	{
		ret = chdir(msh->home);
		msh->last_valid_path = msh->home;
	}
	else
	{
		printf("cd: HOME not set\n");
		return (1);
	}
	return (ret);
}

static int	change_dir_expand(t_msh *msh, char *token)
{
	char	*path;

	path = expand_var(msh, token);
	return (change_dir_helper(msh, path));
}

int	change_dir(t_msh **msh, char **tokens)
{
	t_msh	*m;
	int		ret;

	ret = 0;
	m = *msh;
	if (!tokens[1])
		ret = change_dir_default(m);
	else if (tokens[1][0] == '$')
		ret = change_dir_expand(m, tokens[1]);
	else
		ret = change_dir_helper(m, ft_strdup(tokens[1]));
	return (ret);
}
