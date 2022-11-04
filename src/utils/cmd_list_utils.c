/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:48:47 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/10/26 19:48:49 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_link_cmd_list(t_cmd_list **astack, t_cmd_list *new)
{
	t_cmd_list	*tmp;

	tmp = *astack;
	if (!tmp)
		*astack = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_cmd_list	*new_link_cmd_list(char *cmd, int exp)
{
	t_cmd_list *tmp;

	tmp = malloc(sizeof(*tmp));
	if (!tmp)
		return (NULL);
	tmp->cmd = ft_strdup(cmd);
	tmp->to_expand = exp;
	tmp->next = NULL;
	return (tmp);
}

int		have_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	splitter(char *str, t_msh *msh)
{
	char	**rt;
	int		i;
	t_cmd_list *new_link;

	i = 0;
	rt = ft_split(str, '|');
	while (rt[i])
	{
		new_link = new_link_cmd_list(rt[i], have_expand(rt[i]));
		if (!new_link)
			return (EXIT_FAILURE);
		add_link_cmd_list(&msh->cmd_list, new_link);
		i++;
	}
	return (EXIT_SUCCESS);
}
