/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:17:56 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/26 19:30:38 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char		*ptr;
	unsigned char		value;
	size_t				i;

	if (n > 0)
	{
		i = 0;
		ptr = (unsigned char *) s;
		value = (unsigned char) c;
		while (i < n)
		{
			*ptr = value;
			ptr++;
			i++;
		}
	}
	return (s);
}

size_t	ft_copy(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	else
	{
		size--;
		while (i < size && src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (i);
}

char	*ft_string_dup(const char *s)
{
	char	*output;

	output = (char *) malloc(ft_strlen(s) + 1);
	if (!output)
		return (NULL);
	ft_copy(output, (char *)s, 0);
	return (output);
}

char	*ft_get_substring(char const *s, size_t start, size_t len)
{
	char	*substring;

	if (!s)
		return (NULL);
	substring = (char *) malloc(len + 1);
	if (!substring)
		return (NULL);
	ft_copy(substring, (char *) &s[start], len + 1);
	return (substring);
}

char	*ft_int_to_string(long n)
{
	char	*output;
	long	tmp;
	size_t	i;
	int		sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	tmp = (long) n * sign;
	i = ft_get_int_len(tmp, sign);
	output = malloc(i + 1);
	if (!output)
		return (NULL);
	output[i--] = '\0';
	while (tmp > 9)
	{
		output[i] = (char)(tmp % 10) + '0';
		tmp = tmp / 10;
		i--;
	}
	output[i] = (char)(tmp % 10) + '0';
	if (sign == -1)
		output[0] = '-';
	return (output);
}

size_t	ft_get_int_len(long n, int sign)
{
	size_t	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	if (sign == -1)
		i++;
	return (i);
}

int		ft_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

size_t	ft_count_of_in_str(const char *s, const char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}

char	*ft_char_in_str(const char *s, const char c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_realloc(char *s1, char *s2, int free_s1, int free_s2)
{
	ssize_t		s1_len;
	char		*output;

	s1_len = ft_strlen(s1);
	output = (char *)malloc(s1_len + ft_strlen(s2) + 1);
	if (!output)
		return (NULL);
	ft_copy(output, s1, 0);
	ft_copy(&output[s1_len], s2, 0);
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (output);
}
