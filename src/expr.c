/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:06:35 by dsy               #+#    #+#             */
/*   Updated: 2023/01/10 16:28:27 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_var_to_expr(t_expr *expr, char *data)
{
	t_expr	*new;

	new = expr;
	if (!expr || !data)
		return (0);
	while (new->next != NULL)
		new = new->next;
	new->next = malloc(sizeof(t_expr));
	new->next->data = ft_strdup(data);
	new->next->next = NULL;
	return (1);
}

void	free_expr(t_msh **mshh)
{
	t_msh	*msh;
	t_expr	*cur;

	msh = *mshh;
	if (!msh->exp)
		return ;
	while (msh->exp->next != NULL)
	{
		cur = msh->exp;
		free(msh->exp->data);
		msh->exp = msh->exp->next;
		free(cur);
	}
	if (msh->exp)
	{
		free(msh->exp->data);
		free(msh->exp);
	}
	msh->exp = NULL;
}

int	load_expr(t_msh *msh)
{
	int		i;
	int		end;
	char	**expr;

	i = 0;
	end = 1;
	expr = NULL;
	while (msh->prompt[i] && end)
	{
		if (msh->prompt[i] == '|')
		{
			expr = ft_split(msh->prompt, '|');
			end = 0;
		}
		i++;
	}
	i = 0;
	if (expr != NULL)
	{
		while (expr[i])
			add_var_to_expr(msh->exp, expr[i++]);
		free_split(expr);
		return (1);
	}
	return (0);
}
