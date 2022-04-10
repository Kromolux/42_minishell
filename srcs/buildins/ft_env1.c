/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:25:14 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 09:58:35 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_data *data, t_command *cmd)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_char_in_str(tmp->var, '='))
			ft_write_fd_nl(cmd->fd->out, tmp->var);
		tmp = tmp->next;
	}
	return (RETURN_SUCCESS);
}

char	*ft_get_var(char *s)
{
	int		i;

	i = 0;
	if (ft_isdigit(s[i]) || (!ft_isalpha(s[i]) && s[i] != '_'))
		return (ft_get_substring(s, 0, 1));
	while (s[i])
	{
		if (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r') || s[i] == '#')
			break ;
		else if (s[i] == '\"' || s[i] == '\'' || s[i] == '$' || s[i] == '=')
			break ;
		if (s[i] == '?')
		{
			i++;
			break ;
		}
		i++;
	}
	return (ft_get_substring(s, 0, i));
}

int	ft_str_var_cmp(char *var_name, char *var_elem)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (var_name[i] != var_elem[i])
			return (0);
		i++;
	}
	if (var_elem[i] == '=' || var_elem[i] == '\0')
		return (1);
	return (0);
}

t_envp	*ft_get_envp_element(t_envp *lst, char *var)
{
	t_envp	*tmp;
	char	*var_name;

	tmp = lst;
	while (tmp)
	{
		var_name = ft_get_var(var);
		if (ft_str_var_cmp(var_name, tmp->var))
		{
			free((void *) var_name);
			return (tmp);
		}
		if (var_name)
			free((void *) var_name);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_count_of_envp(t_envp *envp)
{
	t_envp	*tmp;
	int		i;

	tmp = envp;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
