/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:23:54 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 10:01:52 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_sign(const char *str, int *i_str);

long	ft_string_to_int(const char *nptr)
{
	long	output;
	int		sign;
	int		i;

	output = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	sign = check_sign(nptr, &i);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		output *= 10;
		output += nptr[i] - '0';
		i++;
	}
	return ((long) output * sign);
}

static int	check_sign(const char *str, int *i_str)
{
	int	sign;
	int	i;

	i = *i_str;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	*i_str = i;
	return (sign);
}

void	ft_write_fd(int fd, char *s)
{
	write(fd, s, ft_strlen(s));
}

void	ft_write_fd_nl(int fd, char *s)
{
	ft_write_fd(fd, s);
	write(fd, "\n", 1);
}

void	ft_print_bits(int input)
{
	int		i;
	char	c;

	i = 31;
	while (i >= 0)
	{
		c = (((input >> i) & 1) + '0');
		write(1, &c, 1);
		i--;
	}
	write(1, "\n", 1);
}
