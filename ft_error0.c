/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:49:25 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/28 21:47:22 by rkaufman         ###   ########.fr       */
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
	else
	{
		write(cmd->re->err, strerror(errnum), ft_strlen(strerror(errnum)));
		write(cmd->re->err, "\n", 1);
	}
	return (errnum);
}
