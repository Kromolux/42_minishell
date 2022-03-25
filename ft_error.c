/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:49:25 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/25 17:58:00 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_error(int errnum, char *cmd)
{
	write(2, PROMPT, ft_strlen(PROMPT));
	write(2, cmd, ft_strlen(cmd));
	if (errnum == 127)
		write(2, ": command not found\n", 20);
	return (errnum);
}