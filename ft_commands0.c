/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:13:01 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/01 21:37:47 by rkaufman         ###   ########.fr       */
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
	output->re->in = STDIN_FILENO;
	output->re->out = STDOUT_FILENO;
	output->re->err = STDERR_FILENO;
	output->re->next = NULL;
	return (output);
}

void	ft_delete_cmd(t_command **commands)
{
	t_command	*tmp;
	t_redirect	*re_tmp;
	int			i;

	while (*commands)
	{
		tmp = *commands;
		*commands = (*commands)->next;
		free(tmp->cmd);
		tmp->cmd = NULL;
		i = 0;
		while (tmp && tmp->argv[i])
		{
			//printf("free %p\n", tmp->argv[i]);
			free(tmp->argv[i]);
			tmp->argv[i] = NULL;
			i++;
		}
		while (tmp && tmp->re)
		{
			re_tmp = tmp->re;
			tmp->re = tmp->re->next;
			free(re_tmp);
			re_tmp = NULL;
		}
		//printf("free %p\n", tmp);
		free(tmp);
		tmp = NULL;
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
	else if (ft_strcmp(cmd->argv[0], "error_codes"))
		return (ft_error_codes(cmd));
	return (-1);
}

void	ft_print_commands(t_command *commands)
{
	int	i;

	//printf("entered print commands\n");
	while (commands)
	{
		//printf("cmd=%s\n", commands->cmd);
		i = 0;
		while (commands->argv && commands->argv[i])
		{
			printf("argc=%i [%s]\n", i, commands->argv[i]);
			i++;
		}
		if (commands)
		//printf("fd in = %i\nfd out = %i\nfd err = %i\n", commands->re->in, commands->re->out, commands->re->err);
		commands = commands->next;
	}
	//printf("end of print commands\n");
}
