/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:08:18 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 09:59:59 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_create_pipe(t_command *cmd)
{
	int	fd[2];

	if (pipe(fd) == RETURN_ERROR)
		return (ft_print_error(cmd, errno, NULL));
	if (cmd->fd->out == STDOUT_FILENO)
		cmd->fd->out = fd[1];
	else
		close(fd[1]);
	if (cmd->next->fd->in == STDIN_FILENO)
		cmd->next->fd->in = fd[0];
	else
		close(fd[0]);
	return (0);
}

int	ft_connect_pipe(t_command *cmd)
{
	if (cmd->fd->in != STDIN_FILENO && cmd->fd->in != RETURN_ERROR)
	{
		dup2(cmd->fd->in, STDIN_FILENO);
		close(cmd->fd->in);
	}
	if (cmd->fd->out != STDOUT_FILENO)
	{
		dup2(cmd->fd->out, STDOUT_FILENO);
		close(cmd->fd->out);
	}
	return (0);
}

int	ft_close_pipe(t_command *cmd)
{
	if (cmd->fd->in != STDIN_FILENO && cmd->fd->in != RETURN_ERROR)
		close(cmd->fd->in);
	if (cmd->fd->out != STDOUT_FILENO)
		close(cmd->fd->out);
	return (0);
}
