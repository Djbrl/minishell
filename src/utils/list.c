/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 00:15:15 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:29:47 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_data_from_env(t_env_var *env, char *name)
{
	t_env_var	*cur;

	cur = env;
	while (cur->next != NULL)
	{
		if (!ft_strncmp(cur->name, name, ft_strlen(cur->name)))
		{
			free(name);
			return (cur->data);
		}
		else
			cur = cur->next;
	}
	if (!ft_strncmp(cur->name, name, ft_strlen(cur->name)))
	{
		free(name);
		return (cur->data);
	}
	free(name);
	return (NULL);
}

int	add_var_to_env(t_env_var *env, char *name, char *data)
{
	t_env_var	*new;

	new = env;
	if (!env || !name)
		return (0);
	while (new->next != NULL)
	{
		if (!ft_strncmp(new->next->name, name, ft_strlen(new->next->name)))
		{
			free(new->next->data);
			new->next->data = ft_strdup(data);
			return (1);
		}
		else
			new = new->next;
	}
	new->next = malloc(sizeof(t_env_var));
	new->next->data = ft_strdup(data);
	new->next->name = ft_strdup(name);
	new->next->next = NULL;
	return (1);
}
