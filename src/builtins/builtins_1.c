/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <dsy@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 11:19:12 by dsy               #+#    #+#             */
/*   Updated: 2020/10/26 14:55:24 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
****************************STATIC FUNCTIONS****************************
*/

static int	var_name_len(char *name)
{
	int	i;

	i = 0;
	while (name[i] != '$' && name[i])
		i++;
	return (i);
}

static void	ftn_msh_echo(char **var, char **arg, t_env_var **env, int i)
{
	char		*t;
	char		*v;
	char		*a;
	t_env_var	*e;

	a = *arg;
	v = *var;
	e = *env;
	v = ft_substr(a, i + 1, var_name_len(a + i + 1));
	t = ft_strdup(get_data_from_env(e, v));
	if (t != NULL)
		ft_putstr(t);
	else
		write(1, "\n", 1);
	free(t);
}

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

/*
** MSH ECHO is ran by msh_echo_runner
*/
int	msh_echo(t_env_var *env, char *arg, t_msh *msh)
{
	int		i;
	char	*var;

	i = 0;
	(void)msh;
	if (arg[0] == '$')
	{
		while (arg[i])
		{
			if (arg[i] == '$' && arg[i + 1] == '$')
				write(1, "$", 1);
			else
			{
				if (arg[i] == '$' && (ft_isalpha(arg[i + 1]) \
				|| arg[i + 1] == '?'))
					ftn_msh_echo(&var, &arg, &env, i);
			}
			i++;
		}
	}
	else
		ft_putstr(arg);
	return (0);
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
