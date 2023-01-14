/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_signal_expr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 00:15:15 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:30:04 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig_n)
{
	if (sig_n == SIGINT)
	{
		write(1, "\n", 1);
		write(1, PROMPTLINE, ft_strlen(PROMPTLINE));
	}
	else
		return ;
}

char	*remove_spaces(const char *str)
{
	int		j;
	int		i;
	int		n;
	char	*res;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	n = strlen(str);
	res = malloc(n + 1);
	while (i < n)
	{
		if (str[i] != ' ')
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

int	expr_len(t_expr *expr)
{
	t_expr	*cur;
	int		i;

	i = 0;
	cur = expr;
	while (cur)
	{
		cur = cur->next;
		i++;
	}
	return (i);
}

int	update_exit_status(t_msh *msh, int status)
{
	char	*tmp;

	tmp = ft_itoa(status);
	add_var_to_env(msh->env, "?", tmp);
	free(tmp);
	return (status);
}
