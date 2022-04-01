/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:17:33 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/01 16:46:17 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_interactive_SIGINT(int sign)
{
	if (sign == SIGINT)
	{
		write(1,"\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_command	*tmp;

	struct sigaction	response;
	sigemptyset(&response.sa_mask);
	response.sa_handler  = ft_interactive_SIGINT;
	response.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &response, NULL);
	data.errnum = 0;
	//sigaction(SIGQUIT, SIG_IGN, NULL);
	(void) argc;
	(void) argv;
	data.envp = ft_copy_envp(envp);
	//signal(SIGQUIT, SIG_IGN);
	//signalhandler! interactive mode
	while (1)
	{
		data.r_line = readline(PROMPT);
		if (data.r_line == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (ft_strlen(data.r_line) > 0)
			add_history(data.r_line);
		ft_parser(&data);
		ft_print_commands(data.c_line);
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
		ft_delete_cmd(data.c_line);
	}
	ft_delete_list(&data.envp);
	if (data.c_line)
		ft_delete_cmd(data.c_line);
	rl_clear_history();
	if (data.r_line)
		free(data.r_line);
	return (data.errnum);
}

int	ft_cycle_cmd(t_data *data)
{
	t_command	*cmd;
	int			result;

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
				ft_print_error(cmd, 127);
				data->errnum = 127;
			}
		}
		ft_close_pipe(cmd);
		cmd = cmd->next;
	}
	return (0);
}
