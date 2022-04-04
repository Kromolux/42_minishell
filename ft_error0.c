/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:49:25 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/04 11:40:11 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_error(t_command *cmd, int errnum, char *filename)
{
	ft_write_fd(cmd->re->err, PROMPT);
	if (filename)
		ft_write_fd(cmd->re->err, filename);
	else
		ft_write_fd(cmd->re->err, cmd->argv[0]);
	if (errnum == 127)
	{
		if (ft_char_in_str(cmd->argv[0], '/'))
			ft_write_fd(cmd->re->err, ": No such file or directory\n");
		else
			ft_write_fd(cmd->re->err, ": command not found\n");
	}
	else if (errnum == 999)
	{
		ft_write_fd(cmd->re->err, ": ");
		ft_write_fd(cmd->re->err, cmd->argv[1]);
		ft_write_fd(cmd->re->err, ": not a valid identifier\n");
		errnum = 1;
	}
	else if (errnum == 888)
	{
		ft_write_fd(cmd->re->err, ": ");
		ft_write_fd(cmd->re->err, cmd->argv[1]);
		ft_write_fd(cmd->re->err, ": numeric argument required\n");
		errnum = 2;
	}
	else if (errnum == 777)
	{
		ft_write_fd(cmd->re->err, ": ");
		ft_write_fd(cmd->re->err, cmd->argv[1]);
		ft_write_fd(cmd->re->err, ": too many arguments\n");
		errnum = 2;
		return (0);
	}
	else
	{
		ft_write_fd(cmd->re->err, ": ");
		ft_write_fd(cmd->re->err, strerror(errnum));
		write(cmd->re->err, "\n", 1);
	}
	return (errnum);
}

int	ft_error_codes(t_command *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < 255)
	{
		write(cmd->re->out, "error code ", 11);
		tmp = ft_int_to_string(i);
		tmp = ft_realloc(tmp, " ", 1, 0);
		write(cmd->re->out, tmp, ft_strlen(tmp));
		write(cmd->re->out, strerror(i), ft_strlen(strerror(i)));
		write(cmd->re->out, "\n", 1);
		i++;
		free(tmp);
	}
	return (0);
}