/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:49:25 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/06 17:08:45 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_error(t_command *cmd, int errnum, char *token)
{
	ft_write_fd(cmd->re->err, PROMPT);
	ft_write_fd(cmd->re->err, cmd->argv[0]);
	if (errnum == ERR_FILE_CMD)
		ft_err_file_cmd(cmd);
	else if (errnum == ERR_SYNTAX)
		ft_err_syntax(cmd, token);
	else if (errnum == ERR_NOT_VALID)
		ft_err_not_valid(cmd, token);
	else if (errnum == ERR_NUMERIC)
		ft_err_numeric(cmd, token);
	else if (errnum == ERR_TOO_ARG)
		ft_err_too_arg(cmd);
	else if (errnum == ERR_CD_FOLDER)
		ft_err_cd_folder(cmd, token);
	else
		ft_err_else(cmd, errnum);
	return (RETURN_ERROR);
}

int	ft_error_codes(t_command *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < 255)
	{
		ft_write_fd(cmd->re->out, "error code ");
		tmp = ft_int_to_string(i);
		tmp = ft_realloc(tmp, " ", 1, 0);
		ft_write_fd(cmd->re->out, tmp);
		ft_write_fd_nl(cmd->re->out, strerror(i));
		i++;
		free(tmp);
	}
	return (RETURN_SUCCESS);
}
