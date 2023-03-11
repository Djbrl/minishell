/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:26:32 by dsy               #+#    #+#             */
/*   Updated: 2023/01/26 11:19:35 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	temp_exit(t_msh *msh)
{
	exit_cmd(msh);
	free_env(msh);
	free_expr(&msh);
	clear_history();
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
