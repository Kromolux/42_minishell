/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 11:12:11 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/11 10:08:03 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_absolute_path(t_data *data, t_command *cmd);
static void	ft_cd_relative_path(t_data *data, t_command *cmd);
static char	*ft_cd_add_folder(char *path, char *folder);
static char	*ft_cd_remove_folder(char *path);

int	ft_cd(t_data *data, t_command *cmd)
{
	char		*old_pwd;
	struct stat	path_check;

	if (!cmd->argv)
		return (RETURN_ERROR);
	if (lstat(cmd->argv->var, &path_check) == RETURN_ERROR)
		return (ft_print_error(cmd, ERR_CD_FOLDER, cmd->argv->var));
	cmd->errnum = 0;
	if (cmd == data->c_line)
	{
		chdir(cmd->argv->var);
		old_pwd = ft_realloc("OLDPWD=", ft_getenv("PWD", data->envp), 0, 0);
		ft_change_envp(data, old_pwd);
		free(old_pwd);
		if (cmd->argv->var[0] == '/')
			ft_absolute_path(data, cmd);
		else
			ft_cd_relative_path(data, cmd);
		ft_change_envp(data, data->pwd);
	}
	return (RETURN_SUCCESS);
}

static void	ft_absolute_path(t_data *data, t_command *cmd)
{
	int	len;

	free(data->pwd);
	data->pwd = ft_realloc("PWD=", cmd->argv->var, 0, 0);
	len = ft_strlen(data->pwd) - 1;
	if (data->pwd[len] == '/')
		data->pwd[len] = '\0';
}

static void	ft_cd_relative_path(t_data *data, t_command *cmd)
{
	char		**new_path;
	int			i;
	struct stat	path_check;

	i = 0;
	if (ft_strcmp(cmd->argv->var, ".") == 1)
		return ;
	new_path = ft_split(cmd->argv->var, '/');
	while (new_path[i])
	{
		if (ft_strcmp(new_path[i], "..") == 1)
		{
			lstat(&data->pwd[4], &path_check);
			data->pwd = ft_cd_remove_folder(data->pwd);
			if (S_ISLNK(path_check.st_mode))
				chdir(&data->pwd[4]);
		}
		else
			data->pwd = ft_cd_add_folder(data->pwd, new_path[i]);
		i++;
	}
	ft_free_char_array(new_path);
}

static char	*ft_cd_add_folder(char *path, char *folder)
{
	char	*output;

	if (ft_strlen(path) > 5)
	{
		output = ft_realloc(path, "/", 1, 0);
		output = ft_realloc(output, folder, 1, 0);
	}
	else
		output = ft_realloc(path, folder, 1, 0);
	return (output);
}

static char	*ft_cd_remove_folder(char *path)
{
	char	*output;
	int		len;

	len = ft_last_pos_in_string(path, '/');
	if (len <= 4)
		output = ft_string_dup("PWD=/");
	else
		output = ft_get_substring(path, 0, len);
	free(path);
	return (output);
}
