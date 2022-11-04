/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsy <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:06:35 by dsy               #+#    #+#             */
/*   Updated: 2022/10/06 11:31:28 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	load_expr(t_msh *msh)
{
	int		i;
	int		free_expr;

	i = 0;
	free_expr = 0;
	while (msh->prompt[i])
	{
		if (msh->prompt[i] == '|')
		{
			msh->expr = ft_split(msh->prompt, '|');
			free_expr = 1;
		}
		i++;
	}
	return (free_expr);
}
