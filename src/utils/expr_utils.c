/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 00:15:15 by dsy               #+#    #+#             */
/*   Updated: 2022/10/06 11:31:35 by dsy              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	add_var_to_expr(t_expr *expr, char *data)
// {
// 	t_expr	*new;

// 	new = expr;
// 	if (!expr || !data)
// 		return (0);
// 	while (new->next != NULL)
// 		new = new->next;
// 	new->next = malloc(sizeof(t_expr));
// 	new->next->data = ft_strdup(data);
// 	new->next->next = NULL;
// 	return (1);
// }

// int	expr_len(t_expr *expr)
// {
// 	t_expr	*cur;
// 	int		i;

// 	i = 0;
// 	cur = expr;
// 	while (cur)
// 	{
// 		cur = cur->next;
// 		i++;
// 	}
// 	return (i);
// }
