/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 20:05:20 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/28 22:13:13 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_do_execve(t_command *cmd, t_data *data)
{
	char	**paths;
	char	*cmd_path;
	//int		pipe_fd[2];

	paths = ft_split(ft_getenv("PATH", data->envp), ':');
	printf("after split\n");
	if (!paths)
		paths = ft_split(DEFAULT_PATH, ':');
	cmd_path = ft_check_path(cmd->argv[0], paths);
	ft_free_char_array(paths);
	printf("path=%s\n", cmd_path);
	if (!cmd_path)
		return (-1);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (execve(cmd_path, cmd->argv, ft_create_envp_array(data->envp)) == -1)
			ft_print_error(cmd, errno);
		exit(0);
	}
	
	//check for memory leaks in children when forking
	
	return (0);
}

char	**ft_create_envp_array(t_envp *envp)
{
	char	**output;
	t_envp	*tmp;
	int		i;

	output = (char **) malloc(ft_count_of_envp(envp) + 1);
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
	while (paths[i])
	{
		test_path = ft_realloc(paths[i], "/", 0, 0);
		test_path = ft_realloc(test_path, cmd, 1, 0);
		printf("test_path=%s\n", test_path);
		if (access(test_path, F_OK) == 0)
			return (test_path);
		free(test_path);
		i++;
	}
	return (NULL);
}
