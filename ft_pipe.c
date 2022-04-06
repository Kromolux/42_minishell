/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:08:18 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/05 08:16:56 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_create_pipe(t_command *cmd)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (ft_print_error(cmd, errno, NULL));
	if (cmd->re->out == STDOUT_FILENO)
		cmd->re->out = fd[1];
	else
		close(fd[1]);
	if (cmd->next->re->in == STDIN_FILENO)
		cmd->next->re->in = fd[0];
	else
		close(fd[0]);
	return (0);
}

int	ft_connect_pipe(t_command *cmd)
{
	if (cmd->re->in != STDIN_FILENO && cmd->re->in != -1)
	{
		dup2(cmd->re->in, STDIN_FILENO);
		close(cmd->re->in);
	}
	if (cmd->re->out != STDOUT_FILENO)
	{
		dup2(cmd->re->out, STDOUT_FILENO);
		close(cmd->re->out);
	}
	return (0);
}

int	ft_close_pipe(t_command *cmd)
{
	if (cmd->re->in != STDIN_FILENO && cmd->re->in != -1)
		close(cmd->re->in);
	if (cmd->re->out != STDOUT_FILENO)
		close(cmd->re->out);
	return (0);
}