/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:44:24 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/07 08:02:00 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_err_cd_folder(t_command *cmd, char *token)
{
	ft_write_fd(cmd->re->err, ": ");
	ft_write_fd(cmd->re->err, token);
	ft_write_fd(cmd->re->err, ": No such file or directory\n");
	cmd->errnum = 1;
}

void	ft_err_else(t_command *cmd, int errnum)
{
	ft_write_fd(cmd->re->err, ": ");
	ft_write_fd_nl(cmd->re->err, strerror(errnum));
	cmd->errnum = errnum;
}
