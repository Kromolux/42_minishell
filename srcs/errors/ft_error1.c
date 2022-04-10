/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:36:48 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 09:59:34 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_err_file_cmd(t_command *cmd)
{
	ft_write_fd(cmd->fd->err, cmd->cmd);
	if (ft_char_in_str(cmd->cmd, '/'))
		ft_write_fd(cmd->fd->err, ": no such file or directory\n");
	else
		ft_write_fd(cmd->fd->err, ": command not found\n");
	cmd->errnum = 127;
}

void	ft_err_syntax(t_command *cmd, char *token)
{
	ft_write_fd(cmd->fd->err, "syntax error near unexpected token `");
	if (token && token[0] == '\0')
		ft_write_fd(cmd->fd->err, "newline");
	else
		ft_write_fd(cmd->fd->err, token);
	ft_write_fd(cmd->fd->err, "'\n");
	cmd->errnum = 258;
}

void	ft_err_not_valid(t_command *cmd, char *token)
{
	ft_write_fd(cmd->fd->err, cmd->cmd);
	ft_write_fd(cmd->fd->err, ": `");
	ft_write_fd(cmd->fd->err, token);
	ft_write_fd(cmd->fd->err, "': not a valid identifier\n");
	cmd->errnum = 1;
}

void	ft_err_numeric(t_command *cmd, char *token)
{
	ft_write_fd(cmd->fd->err, cmd->cmd);
	ft_write_fd(cmd->fd->err, ": ");
	ft_write_fd(cmd->fd->err, token);
	ft_write_fd(cmd->fd->err, ": numeric argument required\n");
	cmd->errnum = 2;
}

void	ft_err_too_arg(t_command *cmd)
{
	ft_write_fd(cmd->fd->err, cmd->argv->var);
	ft_write_fd(cmd->fd->err, ": too many arguments\n");
	cmd->errnum = 2;
}
