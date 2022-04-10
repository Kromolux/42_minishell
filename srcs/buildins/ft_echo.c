/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:28:00 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 09:58:28 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_command *cmd)
{
	t_envp	*argv_tmp;
	t_envp	*valid_argv;
	int		new_line;

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
	valid_argv = argv_tmp;
	while (argv_tmp)
	{
		if (argv_tmp != valid_argv)
			ft_write_fd(cmd->fd->out, " ");
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
	if (input[i] != '-')
		return (0);
	i++;
	while (input[i])
	{
		if (input[i] != 'n' && input[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
