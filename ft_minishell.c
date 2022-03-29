/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:17:33 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/29 10:38:04 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_command	*tmp;

	(void) argc;
	(void) argv;
	data.envp = ft_copy_envp(envp);
	while (1)
	{
		data.r_line = readline(PROMPT);
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
				waitpid(tmp->pid, NULL, 0);
			tmp = tmp->next;
		}
		free(data.r_line);
		ft_delete_cmd(data.c_line);
	}
	ft_delete_list(&data.envp);
	ft_delete_cmd(data.c_line);
	clear_history();
	free(data.r_line);
	return (0);
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
			if (cmd->next)
				ft_create_pipe(cmd);
			result = ft_build_in_exe(cmd, data);
			if (result == 1)
				return (1);
			if (result == -1)
			{
				//printf("result=%i\n", result);
				if (ft_do_execve(cmd, data) == -1)
					ft_print_error(cmd, 127);
			}
		}
		ft_close_pipe(cmd);
		cmd = cmd->next;
	}
	return (0);
}
