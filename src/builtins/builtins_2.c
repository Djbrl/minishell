/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 03:49:17 by dsy               #+#    #+#             */
/*   Updated: 2020/12/07 18:00:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
****************************STATIC FUNCTIONS****************************
* ftn msh export has to be redefined
*/

static int	ftn_msh_export(char **arg, char **data, char **name)
{
	int		i;
	char	*tmp;
	char	*s;

	s = *arg;
	i = 0;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == '=')
		{
			{
				if (s[i + 1] == 0)
					*data = ft_strdup("\0");
				else
					*data = ft_strdup(s + i + 1);
				tmp = ft_strdup(s);
				tmp[i] = 0;
				*name = ft_strdup(tmp);
				free(tmp);
			}
			break ;
		}
		else
		{
			*data = ft_strdup(0);
			tmp = ft_strdup(s);
			tmp[i] = 0;
			*name = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	return (1);
}

static void	ftn_msh_unset(t_env_var **env, t_env_var **prev)
{
	t_env_var	*e;
	t_env_var	*p;

	e = *env;
	p = *prev;
	if (e->next != NULL)
	{
		free(e->name);
		free(e->data);
		p->next = e->next;
		free(e);
	}
	else
	{
		free(e->name);
		free(e->data);
		free(e);
		p->next = NULL;
	}
}

static int	display_export_error(char *error, char *arg, t_msh *msh)
{
	(void)msh;
	if (!(ft_strncmp(error, ENV_ID_ERROR, ft_strlen(error))))
	{
		ft_putnstr("minishell: ", "export: ", NULL, NULL);
		ft_putnstr("'", arg, "'", error);
	}
	else
		ft_putnstr("minishell: ", "unknown error\n", error, NULL);
	return (0);
}

/*
****************************STATIC FUNCTIONS****************************
*/

/*
** MSH EXPORT is ran by msh_export_runner
*/
int	msh_export(t_env_var *env, char *arg, t_msh *msh)
{
	char		*name;
	char		*data;
	int			i;

	i = 0;
	name = NULL;
	data = NULL;
	if (arg == NULL || (!ft_isalpha(arg[0]) && arg[0] != '_'))
	{
		display_export_error(ENV_ID_ERROR, arg, msh);
		return (update_exit_status(msh, 1));
	}
	i = ftn_msh_export(&arg, &data, &name);
	if (i == 0 || !env)
	{
		display_export_error(ENV_ID_ERROR, arg, msh);
		return (update_exit_status(msh, 1));
	}
	add_var_to_env(env, name, data);
	free(name);
	free(data);
	return (update_exit_status(msh, 0));
}

int	msh_unset(t_env_var *env, t_msh *msh)
{
	t_env_var	*prev;
	int			len;

	if (env == NULL || !msh->tokens[1])
	{
		exit_cmd(msh);
		return (update_exit_status(msh, 1));
	}
	len = ft_strlen(msh->tokens[1]);
	while (env->next != NULL && \
		(ft_strncmp(msh->tokens[1], env->name, len) != 0))
	{
		prev = env;
		env = env->next;
	}
	if ((ft_strncmp(msh->tokens[1], env->name, len)) == 0 && \
		ft_strncmp(msh->tokens[1], "?", len))
		ftn_msh_unset(&env, &prev);
	else
		return (update_exit_status(msh, 1));
	exit_cmd(msh);
	return (update_exit_status(msh, 0));
}
