/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:25:14 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/28 22:02:19 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, t_command *cmd)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_char_in_str(tmp->var, '='))
		{
			write(cmd->re->out, tmp->var, ft_strlen(tmp->var));
			write(cmd->re->out, "\n", 1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_get_var(char *s)
{
	int	i;
	char *output;
	
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
			break ;
		else if (s[i] == '\"' || s[i] == '\'' || s[i] == '$' || s[i] == '=')
			break ;
		//add other break conditions here <-
		if (s[i] == '?')
		{
			i++;
			break ;
		}
		i++;
	}
	output = ft_get_substring(s, 0, i);
	return (output);
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
			return (tmp);
		if (var_name)
			free(var_name);
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
