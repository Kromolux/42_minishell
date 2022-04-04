/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:17:33 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/04 22:06:54 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_command	*tmp;

	g_ctrl_c = 0;
	ft_initialize(&data);
	sigemptyset(&data.response.sa_mask);
	sigaddset(&data.response.sa_mask, SIGCHLD);
	data.response.sa_handler  = ft_interactive_sigint;
	data.response.sa_flags = SA_NOCLDSTOP;
	sigaction(SIGINT, &data.response, NULL);
	sigemptyset(&data.child.sa_mask);
	data.child.sa_handler = ft_child_crash;
	data.child.sa_flags = SA_SIGINFO;
	sigaction(SIGCHLD, &data.child, NULL);
	signal(SIGQUIT, SIG_IGN);
	data.errnum = 0;
	(void) argc;
	(void) argv;
	data.envp = ft_copy_envp(envp);
	while (1)
	{
		data.r_line = readline(PROMPT);
		//data.r_line = ft_get_next_line(STDIN_FILENO);
		if (data.r_line == NULL)
		{
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (ft_strlen(data.r_line) > 0)
			add_history(data.r_line);
		ft_parser(&data);
		//ft_print_commands(data.c_line);
		if (ft_cycle_cmd(&data))
			break ;
		tmp = data.c_line;
		while (tmp)
		{
			if (tmp->pid != 0)
				waitpid(tmp->pid, NULL, WUNTRACED);
			if (g_ctrl_c == 130)
			{
				data.errnum = 130;
				g_ctrl_c = 0;
			}
			tmp = tmp->next;
		}
		free(data.r_line);
		ft_delete_cmd(&data.c_line);
	}
	ft_delete_list(&data.envp);
	if (data.c_line)
		ft_delete_cmd(&data.c_line);
	rl_clear_history();
	if (data.r_line)
		free(data.r_line);
	return (data.errnum);
}

void	ft_initialize(t_data *data)
{
	data->c_line = NULL;
	data->r_line = NULL;
	data->envp = NULL;
	data->errnum = 0;
}

int	ft_cycle_cmd(t_data *data)
{
	t_command	*cmd;
	int			result;

	//printf("entered cycle cmd\n");
	cmd = data->c_line;
	while (cmd)
	{
		if (cmd->argv[0] && cmd->argv[0][0])
		{
			//ft_redirect(cmd);
			if (cmd->next)
				ft_create_pipe(cmd);
			result = ft_build_in_exe(cmd, data);
			if (result == 2)
				return (1);
			if (result == -1)
			{
				data->errnum = ft_do_execve(cmd, data);
				if (data->errnum == 127)
					ft_print_error(cmd, 127, NULL);
			}
			else if (result != 999)
				data->errnum = result;
		}
		ft_close_pipe(cmd);
		cmd = cmd->next;
	}
	return (0);
}
