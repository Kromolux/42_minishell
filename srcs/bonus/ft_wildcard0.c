/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 09:00:38 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 09:57:39 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_wildcard(t_command *cmd, char *input)
{
	t_envp	*new_list;

	new_list = ft_prepare_list(input);
	ft_sort_list(&new_list);
	if (!cmd->cmd)
	{
		cmd->cmd = new_list->var;
		new_list = new_list->next;
	}
	ft_lstadd_back(&cmd->argv, new_list);
	return (RETURN_SUCCESS);
}

t_envp	*ft_apply_filter(t_envp *in_list, char **filter)
{
	t_envp	*out_list;
	int		size;
	int		len;

	out_list = NULL;
	size = 0;
	while (filter[size])
		size++;
	size--;
	len = ft_strlen(filter[0]);
	while (in_list)
	{
		if (ft_check_element(in_list, filter, len, size)
			== RETURN_TRUE)
			ft_lstadd_back(&out_list, ft_lstnew(in_list->var));
		in_list = in_list->next;
	}
	return (out_list);
}

t_return	ft_check_element(t_envp *list, char **filter, int len, int size)
{
	int		i;
	int		pos;
	int		var_len;
	char	*tmp;

	var_len = ft_strlen(list->var);
	i = 1;
	if (ft_strncmp(filter[0], list->var, len) != 0)
		return (RETURN_FALSE);
	pos = len;
	while (i < size)
	{
		tmp = ft_strnstr(&list->var[pos], filter[i], var_len);
		if (tmp == NULL)
			return (RETURN_FALSE);
		pos = (tmp - list->var) + ft_strlen(filter[i]);
		i++;
	}
	if (ft_strcmp(filter[size],
			&list->var[var_len - ft_strlen(filter[size])]) != 1)
		return (RETURN_FALSE);
	return (RETURN_TRUE);
}

char	**ft_get_filter(char *filter)
{
	char	**output;
	int		i;

	if (filter[0] == '*')
		filter = ft_realloc("#", filter, 0, 1);
	if (filter[ft_strlen(filter) - 1] == '*')
		filter = ft_realloc(filter, "#", 1, 0);
	output = ft_split(filter, '*');
	output[0] = ft_remove_char(output[0], '#');
	i = 0;
	while (output[i])
	{
		ft_replace_in_string(output[i], (unsigned char) 255, '*');
		i++;
	}
	i--;
	output[i] = ft_remove_char(output[i], '#');
	free((void *) filter);
	return (output);
}

t_envp	*ft_get_files(char *path)
{
	struct dirent	*content;
	DIR				*dir;
	t_envp			*list;

	list = NULL;
	dir = opendir(path);
	if (!dir)
		return (NULL);
	content = readdir(dir);
	while (content)
	{
		if (content->d_name[0] != '.')
			ft_lstadd_back(&list, ft_lstnew(content->d_name));
		content = readdir(dir);
	}
	closedir(dir);
	free((void *) path);
	return (list);
}
