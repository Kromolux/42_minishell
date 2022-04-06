/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:26:25 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/06 19:00:23 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_command *cmd)
{
	char	*output;

	output = (char *) malloc(BUFFER_SIZE);
	getcwd(output, BUFFER_SIZE);
	if (!output)
		return (RETURN_ERROR);
	ft_write_fd_nl(cmd->re->out, output);
	free(output);
	return (RETURN_SUCCESS);
}
