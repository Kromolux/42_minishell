/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:17:33 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/25 21:16:20 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		*tmp;
	t_command	*commands;
	t_envp		*envp_list;
	int			errnum;

	(void) argc;
	(void) argv;
	envp_list = ft_copy_envp(envp);
	while (1)
	{
		input = readline(PROMPT);
		tmp = ft_skip_whitespaces(input);
		commands = ft_create_cmd(tmp);
		ft_print_commands(commands);
		if (ft_strncmp(commands->cmd, "exit", ft_strlen(commands->cmd)) == 0)
			break ;
		else if (ft_strncmp(commands->cmd, "pwd", ft_strlen(commands->cmd)) == 0)
			ft_pwd();
		else if (ft_strncmp(commands->cmd, "env", ft_strlen(commands->cmd)) == 0)
			ft_env(envp_list);
		else if (ft_strncmp(commands->cmd, "$", 1) == 0)
		{
			if (commands->cmd[1] == '?')
				ft_print_error(errnum, ft_int_to_string(errnum));
			else
				printf("%s\n", ft_getenv(&commands->cmd[1], envp_list));
		}
		else
		{
			errnum = 127;
			ft_print_error(errnum, commands->cmd);
		}
		if (ft_strlen(input) > 0)
			add_history(input);
		free(input);
		ft_delete_cmd(commands);
	}
	ft_delete_list(&envp_list);
	ft_delete_cmd(commands);
	free(input);
	return (0);
}

void	ft_print_commands(t_command *commands)
{
	int	i;

	while (commands)
	{
		printf("cmd=%s\n", commands->cmd);
		i = 0;
		while (commands->argv[i])
		{
			printf("argc=%i %s\n", i, commands->argv[i]);
			i++;
		}
		commands = commands->next;
	}
}

t_command *ft_create_cmd(char *cmd)
{
	t_command	*output;
	int			i;
	int			len;
	int			argc;
	int			quote;
	
	argc = 0;
	output = (t_command *) malloc(sizeof(t_command));
	if (!output)
		return (NULL);
	ft_memset((void *) output, 0, sizeof(t_command));
	quote = ft_quote(cmd);
	i = ft_end_of_token(cmd);
	len = i - quote * 2;
	output->cmd = ft_get_substring(cmd, quote, len);
	while (cmd[i])
	{
		cmd = ft_skip_whitespaces(&cmd[i]);
		quote = ft_quote(cmd);
		i = ft_end_of_token(cmd);
		len = i - quote * 2;
		output->argv[argc] = ft_remo_dq(ft_get_substring(cmd, quote, len));
		argc++;
	}
	return (output);
}

char	*ft_remo_dq(char *s)
{
	char	*output;
	char	*tmp;
	int		i;
	int		quote;

	quote = ft_count_of_in_str(s, '\"');
	if (quote == 0)
		return (s);
	tmp = s;
	output = (char *) malloc((ft_strlen(s) - quote) + 1);
	if (!output)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != '\"')
		{
			output[i] = *s;
			i++;
		}
		s++;
	}
	output[i] = '\0';
	free(tmp);
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
		free(tmp->cmd);
		i = 0;
		while (tmp->argv[i])
		{
			free(tmp->argv[i]);
			i++;
		}
		free(tmp);
	}
}

int	ft_quote(char *cmd)
{
	if (cmd[0] == '\"')
		return (1);
	else
		return (0);
}

void	ft_env(t_envp *envp_list)
{
	while (envp_list)
	{
		write(1, envp_list->var, ft_strlen(envp_list->var));
		write(1, "\n", 1);
		envp_list = envp_list->next;
	}
}

void	ft_pwd(void)
{
	char	*output;

	output = (char *) malloc(BUFFER_SIZE);
	getcwd(output, BUFFER_SIZE);
	if (!output)
		return ;
	printf("%s\n", output);
	free(output);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] < s2[i])
			return ((unsigned char) s1[i] - s2[i]);
		else if (s1[i] > s2[i])
			return ((unsigned char) s1[i] - s2[i]);
		else if (s1[i] == '\0' || s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;
	char	*ptr;

	i = 0;
	little_len = ft_strlen(little);
	ptr = (char *) big;
	if (little_len == 0)
		return (ptr);
	if (little_len > ft_strlen(big))
		return (NULL);
	while (i + little_len <= len)
	{
		if (big[i] == little[0])
		{
			if (ft_strncmp(&big[i], little, little_len) == 0)
				return (&ptr[i]);
		}
		i++;
	}
	return (NULL);
}
