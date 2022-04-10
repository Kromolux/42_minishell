/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:57:11 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 09:58:46 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_swap(t_envp **first, t_envp *swap_a)
{
	t_envp	*tmp;
	t_envp	*swap_b;

	if (!first || !swap_a)
		return ;
	tmp = *first;
	while (tmp && tmp != swap_a && tmp->next != swap_a)
		tmp = tmp->next;
	swap_b = swap_a->next;
	swap_a->next = swap_b->next;
	swap_b->next = swap_a;
	if (*first == swap_a)
	{
		*first = swap_b;
	}
	else
		tmp->next = swap_b;
}

void	ft_add_quotes(t_envp *envp)
{
	t_envp	*tmp;
	char	*new_value;
	int		len;

	tmp = envp;
	while (tmp)
	{
		len = (ft_pos_in_string(tmp->var, '='));
		if (len == (int) ft_strlen(tmp->var))
			len = 0;
		if (len > 0)
		{
			new_value = (char *) malloc(ft_strlen(tmp->var) + 3);
			len++;
			ft_copy(new_value, tmp->var, len + 1);
			ft_copy(&new_value[len], "\"", 0);
			ft_copy(&new_value[len + 1], &tmp->var[len], 0);
			len = ft_strlen(new_value);
			ft_copy(&new_value[len], "\"", 0);
			free((void *) tmp->var);
			tmp->var = new_value;
		}
		tmp = tmp->next;
	}
}

t_envp	*ft_copy_envp_list(t_envp *envp)
{
	t_envp	*output;
	t_envp	*tmp;

	output = (ft_lstnew(envp->var));
	tmp = envp->next;
	while (tmp)
	{
		ft_lstadd_back(&output, ft_lstnew(tmp->var));
		tmp = tmp->next;
	}
	return (output);
}
