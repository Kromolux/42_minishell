/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:28:00 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/09 11:18:24 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_command *cmd)
{
	t_envp	*argv_tmp;
	int	new_line;

	new_line = 1;
	argv_tmp = cmd->argv;
	while (argv_tmp)
	{
		if (ft_valid_option(argv_tmp->var))
			new_line = 0;
		else
			break ;
		argv_tmp = argv_tmp->next;
	}
	argv_tmp = cmd->argv;
	while (argv_tmp)
	{
		if (!argv_tmp->next && argv_tmp->var[0] == ' ')
			break ;
		ft_write_fd(cmd->fd->out, argv_tmp->var);
		argv_tmp = argv_tmp->next;
	}
	if (new_line)
		write(cmd->fd->out, "\n", 1);
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
