/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:05:20 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/05 15:32:28 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_do_execve(t_command *cmd, t_data *data)
{
	char	**paths;
	char	*cmd_path;

	paths = ft_split(ft_getenv("PATH", data->envp), ':');
	cmd_path = ft_check_path(cmd->argv[0], paths);
	ft_free_char_array(paths);
	if (!cmd_path)
		return (127);
	if (cmd->re->in == -1)
	{
		free(cmd_path);
		return (1);
	}
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (ft_print_error(cmd, errno, NULL));
	if (cmd->pid == 0)
		ft_child_process(cmd, data, cmd_path);
	free(cmd_path);
	return (0);
}

void	ft_child_process(t_command *cmd, t_data *data, char *cmd_path)
{
	char	**envp;

	ft_set_child_active();
	ft_connect_pipe(cmd);
	envp = ft_create_envp_array(data->envp);
	if (execve(cmd_path, cmd->argv, envp) == -1)
		ft_print_error(cmd, errno, NULL);
	ft_close_pipe(cmd);
	ft_free_char_array(envp);
	ft_delete_list(&data->envp);
	ft_delete_cmd(&data->c_line);
	free(cmd_path);
	exit(0);
}

char	**ft_create_envp_array(t_envp *envp)
{
	char	**output;
	t_envp	*tmp;
	int		i;

	output = (char **) malloc((ft_count_of_envp(envp) + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	tmp = envp;
	i = 0;
	while (tmp)
	{
		output[i] = ft_string_dup(tmp->var);
		tmp = tmp->next;
		i++;
	}
	output[i] = NULL;
	return (output);
}

char	*ft_check_path(char *cmd, char **paths)
{
	char	*test_path;
	int		i;

	i = 0;
	if (ft_char_in_str(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_string_dup(cmd));
	}
	while (paths && paths[i])
	{
		test_path = ft_realloc(paths[i], "/", 0, 0);
		test_path = ft_realloc(test_path, cmd, 1, 0);
		if (access(test_path, F_OK) == 0)
			return (test_path);
		free(test_path);
		i++;
	}
	return (NULL);
}
