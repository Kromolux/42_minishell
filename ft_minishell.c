/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:17:33 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/21 15:53:33 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (ft_strncmp(input, "exit", 4) == 0)
			break ;
		else if (ft_strncmp(input, "pwd", 3) == 0)
			ft_pwd();
		ft_pipes(input);
		if (ft_strlen(input) > 0)
			add_history(input);
		printf(PROMPT"%s\n", input);
		free(input);
	}
	//printf("input=[%s]\n", input);
	add_history(input);
	//rl_redisplay
	rl_redisplay();
	free(input);
	return (0);
}

void	ft_pipes(char *input)
{

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
/*
char	*ft_echo(char *args)
{
	char	*output;


	return (output);
}

void	ft_exit(void)
{

}
*/
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

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
