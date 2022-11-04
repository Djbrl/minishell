/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamrabhi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:28:02 by jamrabhi          #+#    #+#             */
/*   Updated: 2022/10/19 22:28:08 by jamrabhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_cmd_list
{
	char				*cmd;
	int					to_expand;
	struct s_cmd_list	*next;
}				t_cmd_list;

typedef struct s_data
{
	t_cmd_list	*cmd_list;
}				t_data;

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

int	splitter(char *str, t_data *data)
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
		add_link_cmd_list(&data->cmd_list, new_link);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	print_list(t_data *data)
{
	int i = 0;
	
	while (data->cmd_list->next != NULL)
	{
		printf("----#%d----\n", i);
		printf("cmd = '%s'\n", data->cmd_list->cmd);
		printf("to_expand = '%d'\n", data->cmd_list->to_expand);
		i++;
		data->cmd_list = data->cmd_list->next;
	}
	printf("----#%d----\n", i);
	printf("cmd = '%s'\n", data->cmd_list->cmd);
	printf("to_expand = '%d'\n", data->cmd_list->to_expand);
}

int		main(int ac, char *av[])
{
	t_data	data;

	ft_bzero(&data, sizeof(data));
	if (ac > 1)
	{
		if (splitter(av[1], &data) == EXIT_FAILURE)
		{
			printf("have failed\n");
			return (EXIT_FAILURE);
		}
	}
	print_list(&data);
	return (0);
}
