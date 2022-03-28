/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:13:01 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/28 21:03:08 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	output->re->in = 0;
	output->re->out = 1;
	output->re->err = 2;
	output->re->next = NULL;
	return (output);
}

void	ft_delete_cmd(t_command *commands)
{
	t_command	*tmp;
	int			i;

	while (commands)
	{
		tmp = commands;
		commands = commands->next;
		//free(tmp->cmd);
		i = 0;
		while (tmp->argv[i])
		{
			//printf("free %p\n", tmp->argv[i]);
			free(tmp->argv[i]);
			i++;
		}
		//printf("free %p\n", tmp);
		free(tmp);
	}
}
/*
t_command *ft_create_cmd(char *input)
{
	t_command	*output;
	int			len;
	int			argc;
	int			quote;
	
	argc = 0;
	output = (t_command *) malloc(sizeof(t_command));
	if (!output)
		return (NULL);
	ft_memset((void *) output, 0, sizeof(t_command));
	len = ft_end_of_token(input);
	output->cmd = ft_get_substring(input, 0, len);

	while (input[len])
	{
		input = ft_skip_whitespaces(&input[len]);
		quote = ft_quote(input);
		len = ft_end_of_token(input);
		output->argv[argc] = ft_remove_char(ft_get_substring(input, 0, len), '\"');
		argc++;
	}
	return (output);
}
*/

int	ft_build_in_exe(t_command *cmd, t_data *data)
{
	if (ft_strcmp(cmd->argv[0], "exit"))
		return (1);
	else if (ft_strcmp(cmd->argv[0], "pwd"))
		return (ft_pwd(cmd));
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
	/*
	else
	{
		data->errnum = 127;
		ft_print_error(data);
	}
	*/
	return (-1);
}

void	ft_print_commands(t_command *commands)
{
	int	i;

	while (commands)
	{
		//printf("cmd=%s\n", commands->cmd);
		i = 0;
		while (commands->argv[i])
		{
			printf("argc=%i [%s]\n", i, commands->argv[i]);
			i++;
		}
		commands = commands->next;
	}
	//printf("end of print commands\n");
}
