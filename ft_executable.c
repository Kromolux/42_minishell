/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:05:20 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/03 11:49:54 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_do_execve(t_command *cmd, t_data *data)
{
	char	**paths;
	char	**envp;
	char	*cmd_path;

	//printf("searching for path\n");
	paths = ft_split(ft_getenv("PATH", data->envp), ':');
	if (!paths)
		paths = ft_split(DEFAULT_PATH, ':');
	cmd_path = ft_check_path(cmd->argv[0], paths);
	ft_free_char_array(paths);
	if (!cmd_path)
		return (-1);
	//printf("found path %s\n", cmd_path);
	if (cmd->re->in == -1)
	{
		free(cmd_path);
		return (0);
	}
	cmd->pid = fork();
	//printf("after forking pid=%i\n", cmd->pid);
	if (cmd->pid < 0)
	{
		printf("fork failed!\n");
		return (ft_print_error(cmd, errno, NULL));
	}
	if (cmd->pid == 0)
	{
		//add signalhandler here <-
		sigaction(SIGINT, NULL, NULL);
		//printf("child executing ->%s\n", cmd_path);
		ft_connect_pipe(cmd);
		envp = ft_create_envp_array(data->envp);
		
		if (execve(cmd_path, cmd->argv, envp) == -1)
			ft_print_error(cmd, errno, NULL);
		printf("execve failed!\n");
		//free(cmd_path);
		//ft_free_char_array(envp);
		//free everything...
		exit(0);
	}
	free(cmd_path);
	//check for memory leaks in children when forking
	return (0);
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
	while (paths[i])
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
