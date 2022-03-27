/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:25:14 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/27 13:23:49 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_var(char *s)
{
	int	i;
	char *output;
	
	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
			break ;
		else if (s[i] == '\"' || s[i] == '\'' || s[i] == '$')
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

void	ft_env(t_data *data)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_char_in_str(tmp->var, '='))
		{
			write(data->c_line->re->out, tmp->var, ft_strlen(tmp->var));
			write(data->c_line->re->out, "\n", 1);
		}
		tmp = tmp->next;
	}
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
	if (var_elem[i] == '=')
		return (1);
	return (0);
}
