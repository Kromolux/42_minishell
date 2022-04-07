/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:26:25 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/07 15:53:31 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data, t_command *cmd)
{
	ft_write_fd_nl(cmd->re->out, &data->pwd[ft_pos_in_string
		(data->pwd, '=') + 1]);
	return (RETURN_SUCCESS);
}
