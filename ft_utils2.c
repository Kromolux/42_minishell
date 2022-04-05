/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:20:39 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/05 08:50:16 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pos_in_string(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
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

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] == '\0' || s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

/*
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
*/
