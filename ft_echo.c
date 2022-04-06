/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:28:00 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/06 13:07:35 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_command *cmd)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 1;
	while (cmd->argv[i])
	{
		if (ft_valid_option(cmd->argv[i]))
			new_line = 0;
		else
			break ;
		i++;
	}
	while (cmd->argv[i])
	{
		if (!cmd->argv[i + 1] && cmd->argv[i][0] == ' ')
			break ;
		ft_write_fd(cmd->re->out, cmd->argv[i]);
		i++;
	}
	if (new_line)
		write(cmd->re->out, "\n", 1);
	return (RETURN_SUCCESS);
}

int	ft_valid_option(char *input)
{
	int	i;

	i = 0;
	if (input[i] != '-' && input[i] != ' ')
		return (0);
	else if (input[i] == ' ')
		return (1);
	i++;
	while (input[i])
	{
		if (input[i] != 'n' && input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
