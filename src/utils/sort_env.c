/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 00:48:20 by jamrabhi          #+#    #+#             */
/*   Updated: 2023/02/27 00:48:23 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_env(t_env_var *env_a, t_env_var *env_b)
{
	char	*tmp_name;
	char	*tmp_data;

	tmp_name = env_a->name;
	tmp_data = env_a->data;
	env_a->name = env_b->name;
	env_a->data = env_b->data;
	env_b->name = tmp_name;
	env_b->data = tmp_data;
}

t_env_var	*env_duplicate(t_env_var *lst)
{
	t_env_var	*new_lst;
	t_env_var	*new_node;
	t_env_var	**new_tail;

	new_lst = NULL;
	new_tail = &new_lst;
	while (lst)
	{
		new_node = malloc(sizeof(t_env_var));
		if (!new_node)
			return (NULL);
		new_node->name = ft_strdup(lst->name);
		new_node->data = ft_strdup(lst->data);
		new_node->next = NULL;
		*new_tail = new_node;
		new_tail = &new_node->next;
		lst = lst->next;
	}
	return (new_lst);
}

void	free_env_cpy(t_env_var *env)
{
	t_env_var	*cur;

	while (env)
	{
		cur = env;
		env = env->next;
		free(cur->data);
		free(cur->name);
		free(cur);
	}
}

void	sort_env(t_env_var *env)
{
	t_env_var	*env_cpy;
	t_env_var	*env_cpy2;

	env_cpy = env;
	while (env_cpy)
	{
		env_cpy2 = env_cpy->next;
		while (env_cpy2)
		{
			if (ft_strcmp(env_cpy->name, env_cpy2->name) > 0)
				swap_env(env_cpy, env_cpy2);
			env_cpy2 = env_cpy2->next;
		}
		env_cpy = env_cpy->next;
	}
}
