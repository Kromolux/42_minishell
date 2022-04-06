/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:12:11 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/06 17:52:37 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_new_path(t_data *data, t_command *cmd, char *output);

int	ft_cd(t_data *data, t_command *cmd)
{
	char	*output;
	int		result;

	if (!cmd->argv[1])
		return (RETURN_ERROR);
	output = (char *) malloc(BUFFER_SIZE);
	if (!output)
		return (RETURN_ERROR);
	ft_copy(output, "OLDPWD=", 0);
	getcwd(&output[7], BUFFER_SIZE);
	result = chdir(cmd->argv[1]);
	if (cmd == data->c_line && result == RETURN_SUCCESS)
		ft_cd_new_path(data, cmd, output);
	else if (result == RETURN_SUCCESS)
		chdir(&output[7]);
	else
	{
		ft_print_error(cmd, ERR_CD_FOLDER, cmd->argv[1]);
		free(output);
		return (RETURN_ERROR);
	}
	free(output);
	return (RETURN_SUCCESS);
}

static void	ft_cd_new_path(t_data *data, t_command *cmd, char *output)
{
	cmd->errnum = 0;
	ft_change_envp(data, output);
	ft_copy(output, "PWD=", 0);
	getcwd(&output[4], BUFFER_SIZE);
	ft_change_envp(data, output);
}
