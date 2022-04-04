/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:12:11 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/04 10:50:04 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_data *data, t_command *cmd)
{
	char	*output;
	int		result;

	if (!cmd->argv[1])
		return (-1);
	output = (char *) malloc(BUFFER_SIZE);
	if (!output)
		return (-1);
	ft_copy(output, "OLDPWD=", 0);
	getcwd(&output[7], BUFFER_SIZE);
	result = chdir(data->c_line->argv[1]);
	if (result == 0)
	{
		ft_change_envp(data, output);
		ft_copy(output, "PWD=", 0);
		getcwd(&output[4], BUFFER_SIZE);
		ft_change_envp(data, output);
	}
	else
	{
		data->errnum = 1;
		ft_copy(output, "cd: ", 0);
		ft_copy(&output[4], data->c_line->argv[1], 0);
		ft_print_error(cmd, errno, output);
		free(output);
		return (1);
	}
	free(output);
	return (0);
}
