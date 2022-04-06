/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:17:33 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/06 13:01:51 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data		data;

	ft_initialize(&data, envp);
	ft_set_parent_interactive();
	(void) argc;
	(void) argv;
	while (1)
	{
		data.r_line = readline(PROMPT);
		if (data.r_line == NULL)
			break ;
		if (ft_strlen(data.r_line) > 0)
			add_history(data.r_line);
		ft_parser(&data);
		//ft_print_commands(data.c_line);
		if (ft_cycle_cmd(&data) == RETURN_EXIT)
			break ;
		ft_wait_for_kids(&data);
		free(data.r_line);
		ft_delete_cmd(&data.c_line);
	}
	ft_clear_mem(&data);
	return (data.errnum);
}

void	ft_clear_mem(t_data *data)
{
	ft_delete_list(&data->envp);
	if (data->c_line)
		ft_delete_cmd(&data->c_line);
	rl_clear_history();
	if (data->r_line)
		free(data->r_line);
	else
		ft_write_fd(STDOUT_FILENO, "exit\n");
}

void	ft_wait_for_kids(t_data *data)
{
	t_command	*tmp;
	int			status;

	if (!data->c_line)
		return ;
	tmp = data->c_line;
	status = 0;
	while (tmp)
	{
		if (tmp->pid != 0 && waitpid(tmp->pid, &status, 0) != -1)
		{
			if (WIFEXITED(status))
				tmp->errnum = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				tmp->errnum = 128 + WTERMSIG(status);
		}
		tmp = tmp->next;
	}
	tmp = ft_last_cmd(data->c_line);
	data->errnum = tmp->errnum;
	ft_set_parent_interactive();
}

void	ft_initialize(t_data *data, char **envp)
{
	g_ctrl_c = 0;
	data->envp = ft_copy_envp(envp);
	data->c_line = NULL;
	data->r_line = NULL;
	data->errnum = 0;
}

int	ft_cycle_cmd(t_data *data)
{
	t_command	*cmd;
	int			result;

	ft_set_parent_active();
	cmd = data->c_line;
	while (cmd)
	{
		if (cmd->argv[0] && cmd->argv[0][0])
		{
			if (cmd->next)
				ft_create_pipe(cmd);
			result = ft_build_in_exe(cmd, data);
			if (result == RETURN_EXIT)
				return (RETURN_EXIT);
			if (result == RETURN_FALSE)
				ft_do_execve(cmd, data);
		}
		ft_close_pipe(cmd);
		cmd = cmd->next;
	}
	return (RETURN_SUCCESS);
}
