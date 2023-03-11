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

static void	unset_var(t_env_var **env, t_env_var **prev)
{
	t_env_var	*e;
	t_env_var	*p;

	e = *env;
	p = *prev;
	if (e->next != NULL && p->next != NULL)
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

static int	find_var(char **tokens, t_env_var **envar, t_msh *msh)
{
	t_env_var	*prev;
	t_env_var	*env;
	int			len;

	env = *envar;
	len = ft_strlen(tokens[1]);
	while (env->next != NULL && \
		(ft_strncmp(tokens[1], env->name, len) != 0))
	{
		prev = env;
		env = env->next;
	}
	if ((ft_strncmp(tokens[1], env->name, len)) == 0 && \
		ft_strncmp(tokens[1], "?", len) && \
		(ft_strlen(tokens[1]) == ft_strlen(env->name)))
		unset_var(&env, &prev);
	else
		return (update_exit_status(msh, 1));
	exit_cmd(msh);
	return (update_exit_status(msh, 0));
}

/*
****************************STATIC FUNCTIONS****************************
*/

int	msh_unset(t_env_var *env, t_msh *msh, char *field)
{
	int		free_tokens;
	int		status;
	char	**tokens;

	free_tokens = 0;
	if (field == NULL)
		tokens = msh->tokens;
	else
	{
		tokens = ft_split(field, ' ');
		free_tokens = 1;
	}
	if (env == NULL || !tokens[1])
	{
		exit_cmd(msh);
		return (update_exit_status(msh, 1));
	}
	status = find_var(tokens, &env, msh);
	if (free_tokens)
		free_split(tokens);
	return (status);
}
