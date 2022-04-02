/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:49:25 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/01 21:36:43 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_error(t_command *cmd, int errnum)
{
	write(cmd->re->err, PROMPT, ft_strlen(PROMPT));
	write(cmd->re->err, cmd->argv[0],
		ft_strlen(cmd->argv[0]));
	if (errnum == 127)
		write(cmd->re->err, ": command not found\n", 20);
	else if (errnum == 999)
	{
		write(cmd->re->err, ": ", 2);
		write(cmd->re->err, cmd->argv[1], ft_strlen(cmd->argv[1]));
		write(cmd->re->err, ": not a valid identifier\n", 25);
	}
	else
	{
		write(cmd->re->err, strerror(errnum), ft_strlen(strerror(errnum)));
		write(cmd->re->err, "\n", 1);
	}
	return (errnum);
}

int	ft_error_codes(t_command *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < 255)
	{
		write(cmd->re->out, "error code ", 11);
		tmp = ft_int_to_string(i);
		tmp = ft_realloc(tmp, " ", 1, 0);
		write(cmd->re->out, tmp, ft_strlen(tmp));
		write(cmd->re->out, strerror(i), ft_strlen(strerror(i)));
		write(cmd->re->out, "\n", 1);
		i++;
		free(tmp);
	}
	return (0);
}