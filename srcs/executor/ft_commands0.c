/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:13:01 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 12:28:22 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command	*ft_create_cmd_elem(void)
{
	t_command	*output;

	output = (t_command *) malloc(sizeof(t_command));
	if (!output)
		return (NULL);
	ft_memset((void *) output, 0, sizeof(t_command));
	output->fd = (t_fd *) malloc(sizeof(t_fd));
	if (!output->fd)
		return (NULL);
	output->fd->in = STDIN_FILENO;
	output->fd->out = STDOUT_FILENO;
	output->fd->err = STDERR_FILENO;
	output->result = RETURN_FALSE;
	output->re = NULL;
	return (output);
}

void	ft_delete_cmd(t_command **commands)
{
	t_command	*tmp;

	while (*commands)
	{
		tmp = *commands;
		*commands = (*commands)->next;
		free((void *) tmp->cmd);
		free((void *) tmp->fd);
		tmp->fd = NULL;
		tmp->cmd = NULL;
		ft_delete_list(&tmp->argv);
		ft_lstdel_re(&tmp->re);
		free((void *) tmp);
		tmp = NULL;
	}
}

int	ft_build_in_exe(t_command *cmd, t_data *data)
{
	if (ft_strcmp(cmd->cmd, "exit"))
		return (ft_exit(cmd, data));
	else if (ft_strcmp(cmd->cmd, "pwd"))
		return (ft_pwd(data, cmd));
	else if (ft_strcmp(cmd->cmd, "env"))
		return (ft_env(data, cmd));
	else if (ft_strcmp(cmd->cmd, "export"))
		return (ft_export(data, cmd));
	else if (ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset(data, cmd));
	else if (ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(data, cmd));
	else if (ft_strcmp(cmd->cmd, "echo"))
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->cmd, "error_codes"))
		return (ft_error_codes(cmd));
	return (RETURN_FALSE);
}

void	ft_print_commands(t_command *commands)
{
	t_envp	*tmp;
	int		i;

	while (commands)
	{
		i = 0;
		tmp = commands->argv;
		while (tmp)
		{
			printf("argc=%i [%s]\n", i, tmp->var);
			tmp = tmp->next;
			i++;
		}
		if (commands)
			commands = commands->next;
	}
}
