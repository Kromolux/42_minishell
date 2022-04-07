/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:13:01 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/07 14:01:56 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_delete_redirections(t_command *cmd);

t_command	*ft_create_cmd_elem(void)
{
	t_command	*output;

	output = (t_command *) malloc(sizeof(t_command));
	if (!output)
		return (NULL);
	ft_memset((void *) output, 0, sizeof(t_command));
	output->re = (t_redirect *) malloc(sizeof(t_redirect));
	if (!output->re)
		return (NULL);
	output->re->in = STDIN_FILENO;
	output->re->out = STDOUT_FILENO;
	output->re->err = STDERR_FILENO;
	output->re->next = NULL;
	return (output);
}

void	ft_delete_cmd(t_command **commands)
{
	t_command	*tmp;
	int			i;

	while (*commands)
	{
		tmp = *commands;
		*commands = (*commands)->next;
		free((void *) tmp->cmd);
		tmp->cmd = NULL;
		i = 0;
		while (tmp && tmp->argv[i])
		{
			free((void *) tmp->argv[i]);
			tmp->argv[i] = NULL;
			i++;
		}
		ft_delete_redirections(tmp);
		free((void *) tmp);
		tmp = NULL;
	}
}

int	ft_build_in_exe(t_command *cmd, t_data *data)
{
	if (ft_strcmp(cmd->argv[0], "exit"))
		return (ft_exit(cmd, data));
	else if (ft_strcmp(cmd->argv[0], "pwd"))
		return (ft_pwd(data, cmd));
	else if (ft_strcmp(cmd->argv[0], "env"))
		return (ft_env(data, cmd));
	else if (ft_strcmp(cmd->argv[0], "export"))
		return (ft_export(data, cmd));
	else if (ft_strcmp(cmd->argv[0], "unset"))
		return (ft_unset(data, cmd));
	else if (ft_strcmp(cmd->argv[0], "cd"))
		return (ft_cd(data, cmd));
	else if (ft_strcmp(cmd->argv[0], "echo"))
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->argv[0], "error_codes"))
		return (ft_error_codes(cmd));
	return (RETURN_FALSE);
}

static void	ft_delete_redirections(t_command *cmd)
{
	t_redirect	*re_tmp;

	while (cmd && cmd->re)
	{
		re_tmp = cmd->re;
		cmd->re = cmd->re->next;
		free((void *) re_tmp);
		re_tmp = NULL;
	}
}

void	ft_print_commands(t_command *commands)
{
	int	i;

	while (commands)
	{
		i = 0;
		while (commands->argv[i])
		{
			printf("argc=%i [%s]\n", i, commands->argv[i]);
			i++;
		}
		if (commands)
		commands = commands->next;
	}
}
