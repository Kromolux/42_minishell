/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:17:33 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/03 12:01:29 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_command	*tmp;

	g_ctrl_c = 0;
	sigemptyset(&data.response.sa_mask);
	data.response.sa_handler  = ft_interactive_sigint;
	data.response.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &data.response, NULL);
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
			if (result == 1)
				return (1);
			if (result == -1 && ft_do_execve(cmd, data) == -1)
			{
				ft_print_error(cmd, 127, NULL);
				data->errnum = 127;
			}
		}
		ft_close_pipe(cmd);
		cmd = cmd->next;
	}
	return (0);
}
