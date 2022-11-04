/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:26:32 by dsy               #+#    #+#             */
/*   Updated: 2022/09/15 14:26:34 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_envar(t_msh *msh)
{
	if (msh->home != NULL)
		free(msh->home);
	if (msh->user != NULL)
		free(msh->user);
	if (msh->full_path != NULL)
		free(msh->full_path);
	if (msh->default_path != NULL)
		free(msh->default_path);
	if (msh->paths != NULL)
		free_split(msh->paths);
}

static void	free_env(t_msh *msh)
{
	t_env_var	*cur;

	if (!msh->env)
		return ;
	while (msh->env->next != NULL)
	{
		cur = msh->env;
		free(msh->env->data);
		free(msh->env->name);
		msh->env = msh->env->next;
		free(cur);
	}
	if (msh->env)
	{
		free(msh->env->data);
		free(msh->env->name);
		free(msh->env);
	}
	free_envar(msh);
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	exit_cmd(t_msh *msh)
{
	if (msh->prompt != NULL)
	{
		free(msh->prompt);
		msh->prompt = NULL;
	}
	if (msh->tokens != NULL)
	{
		free_split(msh->tokens);
		msh->tokens = NULL;
	}
}

void	exit_shell(t_msh *msh)
{
	int		exit_status;

	exit_status = ft_atoi(get_data_from_env(msh->env, ft_strdup("?")));
	free_env(msh);
	rl_clear_history();
	exit(exit_status);
}
