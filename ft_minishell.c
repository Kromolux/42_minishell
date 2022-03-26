/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:17:33 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/26 19:24:45 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data		data;

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
		if (ft_build_in_exe(&data))
			break ;
		//ft_execev_fork...
		free(data.r_line);
		ft_delete_cmd(data.c_line);
	}
	ft_delete_list(&data.envp);
	ft_delete_cmd(data.c_line);
	free(data.r_line);
	return (0);
}

char	*ft_get_var(char *s)
{
	int	i;
	char *output;
	
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
			break ;
		else if (s[i] == '\"' || s[i] == '\'')
			break ;
		//add other break conditions here <-
		i++;
	}
	output = ft_get_substring(s, 0, i);
	return (output);
}

int	ft_build_in_exe(t_data *data)
{
	if (ft_strncmp(data->c_line->argv[0], "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(data->c_line->argv[0], "pwd", 3) == 0)
		ft_pwd(data);
	else if (ft_strncmp(data->c_line->argv[0], "env", 3) == 0)
		ft_env(data);
	else if (ft_strncmp(data->c_line->argv[0], "export", 6) == 0)
		ft_export(data);
	else if (ft_strncmp(data->c_line->argv[0], "unset", 5) == 0)
		ft_unset(data);
	else if (ft_strncmp(data->c_line->argv[0], "$", 1) == 0)
	{
		if (data->c_line->argv[0][1] == '?')
			ft_print_error(data->errnum, ft_int_to_string(data->errnum));
		else
			printf("%s\n", ft_getenv(&data->c_line->argv[0][1], data->envp));
	}
	else
	{
		data->errnum = 127;
		ft_print_error(data->errnum, data->c_line->argv[0]);
	}
	return (0);
}

char	*ft_remove_char(char *s, char c)
{
	char	*output;
	char	*tmp;
	int		i;
	int		count;

	count = ft_count_of_in_str(s, c);
	if (count == 0)
		return (s);
	tmp = s;
	output = (char *) malloc((ft_strlen(s) - count) + 1);
	if (!output)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
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

void	ft_env(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		write(data->c_line->re->out, tmp->var, ft_strlen(tmp->var));
		write(data->c_line->re->out, "\n", 1);
		tmp = tmp->next;
	}
}

void	ft_pwd(t_data *data)
{
	char	*output;

	output = (char *) malloc(BUFFER_SIZE);
	getcwd(output, BUFFER_SIZE);
	if (!output)
		return ;
	write(data->c_line->re->out, output, ft_strlen(output));
	write(data->c_line->re->out, "\n", 1);
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
