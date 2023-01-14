/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 03:49:17 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:27:37 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
****************************STATIC FUNCTIONS****************************
* ftn msh export has to be redefined
*/

static int	ftn_export_name(char **s, char **name, int flag, int i)
{
	char	*tmp;

	tmp = ft_strdup(*s);
	if (flag == 1)
		tmp[i] = 0;
	*name = ft_strdup(tmp);
	free(tmp);
	return (flag);
}

static int	ftn_msh_export(char **arg, char **data, char **name)
{
	int		i;
	int		flag;
	char	*s;

	s = *arg;
	i = 0;
	flag = 0;
	while (i < (int)ft_strlen(s))
	{
		if (s[i] == '=')
		{
			flag = 1;
			if (s[i + 1] == 0)
				*data = ft_strdup("\0");
			else
				*data = ft_strdup(s + i + 1);
			break ;
		}
		i++;
	}
	ftn_export_name(&s, name, flag, i);
	return (flag);
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
	if ((i == 0 && name == NULL) || !env)
	{
		display_export_error(ENV_ID_ERROR, arg, msh);
		return (update_exit_status(msh, 1));
	}
	add_var_to_env(env, name, data);
	free(name);
	free(data);
	return (update_exit_status(msh, 0));
}
