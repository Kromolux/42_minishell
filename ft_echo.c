/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:28:00 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/27 17:20:52 by rkaufman         ###   ########.fr       */
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
		write(cmd->re->out, cmd->argv[i], ft_strlen(cmd->argv[i]));
		i++;
	}
	if (new_line)
		write(cmd->re->out, "\n", 1);
	return (0);
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
