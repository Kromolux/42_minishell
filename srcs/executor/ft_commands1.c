/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 10:00:06 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 09:59:52 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_first_cmd(t_command *cmd, t_data *data)
{
	if (cmd != data->c_line)
		return (0);
	return (1);
}

t_command	*ft_last_cmd(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
