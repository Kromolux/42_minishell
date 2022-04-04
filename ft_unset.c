/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:03:13 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/03 18:32:49 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_data *data, t_command *cmd)
{
	t_envp	*tmp;
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		if (!ft_check_validity(cmd->argv[i]))
		{
			data->errnum = 1;
			return (ft_print_error(cmd, 999, NULL));
		}
		tmp = ft_get_envp_element(data->envp, cmd->argv[i]);
		if (tmp)
			ft_delete_envp_elem(&data->envp, tmp);
		i++;
	}
	return (0);
}

void	ft_delete_envp_elem(t_envp **first, t_envp *to_del)
{
	t_envp	*tmp;

	if (!first || !to_del)
		return ;
	tmp = *first;
	while (tmp && tmp != to_del && tmp->next != to_del)
		tmp = tmp->next;
	free(to_del->var);
	if (*first == to_del)
		*first = to_del->next;
	else
		tmp->next = to_del->next;
	free(to_del);
}
