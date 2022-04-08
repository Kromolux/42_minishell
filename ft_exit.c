/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:00:00 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/08 17:51:51 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_return_with_error(t_command *cmd);

int	ft_exit(t_command *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
		i++;
	if (i != 1 && !ft_is_number_only(cmd->argv[1]))
	{
		cmd->errnum = 255;
		ft_print_error(cmd, ERR_NUMERIC, cmd->argv[1]);
		if (cmd == data->c_line && !data->c_line->next)
			return (ft_return_with_error(cmd));
	}
	if (i > 2)
	{
		ft_write_fd(cmd->re->err, "exit\n");
		return (ft_print_error(cmd, ERR_TOO_ARG, NULL));
	}
	if (i >= 2)
		cmd->errnum = (unsigned char) ft_string_to_int(cmd->argv[1]);
	if (cmd != data->c_line || data->c_line->next)
		return (RETURN_ERROR);
	ft_write_fd(cmd->re->err, "exit\n");
	return (RETURN_EXIT);
}

static int	ft_return_with_error(t_command *cmd)
{
	ft_write_fd(cmd->re->err, "exit\n");
	return (RETURN_EXIT);
}

int	ft_is_number_only(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] > '9' || input[i] < '0')
		{
			if (i > 0 || (input[i] != '+' && input[i] != '-')
				|| input[i + 1] < '0' || input[i + 1] > '9')
				return (0);
		}
		i++;
	}
	return (1);
}
