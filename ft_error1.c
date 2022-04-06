/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:36:48 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/06 17:21:41 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_err_file_cmd(t_command *cmd)
{
	if (ft_char_in_str(cmd->argv[0], '/'))
		ft_write_fd(cmd->re->err, ": no such file or directory\n");
	else
		ft_write_fd(cmd->re->err, ": command not found\n");
	cmd->errnum = 127;
}

void	ft_err_syntax(t_command *cmd, char *token)
{
	ft_write_fd(cmd->re->err, "syntax error near unexpected token `");
	if (token && token[0] == '\0')
		ft_write_fd(cmd->re->err, "newline");
	else
		ft_write_fd(cmd->re->err, token);
	ft_write_fd(cmd->re->err, "'\n");
	cmd->errnum = 258;
}

void	ft_err_not_valid(t_command *cmd, char *token)
{
	ft_write_fd(cmd->re->err, ": `");
	ft_write_fd(cmd->re->err, token);
	ft_write_fd(cmd->re->err, "': not a valid identifier\n");
	cmd->errnum = 1;
}

void	ft_err_numeric(t_command *cmd, char *token)
{
	ft_write_fd(cmd->re->err, ": ");
	ft_write_fd(cmd->re->err, token);
	ft_write_fd(cmd->re->err, ": numeric argument required\n");
	cmd->errnum = 2;
}

void	ft_err_too_arg(t_command *cmd)
{
	ft_write_fd(cmd->re->err, ": too many arguments\n");
	cmd->errnum = 2;
}
