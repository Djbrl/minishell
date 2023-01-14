/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_runner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:13:26 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:27:45 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
****************************STATIC FUNCTIONS****************************
*/

static int	list_exports(t_env_var *env, t_msh *msh)
{
	t_env_var	*e;
	int			l;

	(void)msh;
	e = env;
	l = ft_strlen(e->name);
	while (e->next != NULL)
	{
		if (e->name && e->data && ft_strncmp(e->name, "init", l) != 0 && \
			ft_strncmp(e->name, "?", l))
		{
			write(1, "export ", 7);
			ft_putnstr(e->name, "=", e->data, "\n");
		}
		e = e->next;
	}
	if (e->name && e->data && (ft_strncmp(e->name, "init", l) != 0 && \
		ft_strncmp(e->name, "?", l)))
	{
		write(1, "export ", 7);
		ft_putnstr(e->name, "=", e->data, "\n");
	}
	exit_cmd(msh);
	return (update_exit_status(msh, 0));
}

/*
****************************STATIC FUNCTIONS****************************
*/

int	msh_export_runner(t_env_var *env, t_msh *msh)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	(void)msh;
	if (msh->tokens[1] == NULL)
	{
		list_exports(env, msh);
		exit_cmd(msh);
		return (update_exit_status(msh, 0));
	}
	while (msh->tokens[i])
	{
		exit_status = msh_export(env, msh->tokens[i], msh);
		i++;
	}
	exit_cmd(msh);
	return (update_exit_status(msh, exit_status));
}
