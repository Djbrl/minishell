/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 03:49:17 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:28:08 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
****************************STATIC FUNCTIONS****************************
* ftn msh export has to be redefined
*/

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

/*
****************************STATIC FUNCTIONS****************************
*/

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
