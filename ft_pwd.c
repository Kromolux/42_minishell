/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:26:25 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/06 13:03:17 by rkaufman         ###   ########.fr       */
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
	write(cmd->re->out, output, ft_strlen(output));
	write(cmd->re->out, "\n", 1);
	free(output);
	return (RETURN_SUCCESS);
}
