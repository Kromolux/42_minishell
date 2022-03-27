/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:02:37 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/27 21:03:57 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_data *data)
{
	int	i;

	i = 1;
	if (!data->c_line->argv[1])
		ft_var_printing(data);
	while (data->c_line->argv[i])
	{
		if (!ft_check_validity(data->c_line->argv[i]))
			return (ft_print_error(data));
		
		i++;
	}
	return (0);
}

int	ft_check_validity(char *argv)
{
	int	i;

	i = 0;
	if (argv[0] >= '0' && argv[0] >= '9')
		return (0);
	while (argv[i])
	{
		if ((argv[i] < 'A' || argv[i] > 'Z')
			&& (argv[i] < 'a' || argv[i] > 'z')
			&& (argv[i] < '0' || argv[i] > '9')
			&& argv[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_var_printing(t_data *data)
{
	t_envp	*tmp;
	t_envp	*copy;
	//sort list
	copy = ft_copy_envp_list(data->envp);
	ft_add_quotes(copy);
	//ft_sort_list(copy);
	tmp = copy;
	while (tmp)
	{
		write(data->c_line->re->out, EXPORT, ft_strlen(EXPORT));
		write(data->c_line->re->out, tmp->var, ft_strlen(tmp->var));
		write(data->c_line->re->out, "\n", 1);
		tmp = tmp->next;
	}
	ft_delete_list(&copy);
}
/*
void	ft_sort_list(t_envp *envp)
{
	t_envp	*tmp;
	char	*before;
	int		sorted;
	
	sorted = 0;
	while (!sorted)
	{
		sorted = 0;
		tmp = envp;
		while (tmp)
		{
			if (tmp->var[0] > )
		}
	}
}
*/
void	ft_add_quotes(t_envp *envp)
{
	t_envp	*tmp;
	char	*new_value;
	int		len;

	tmp = envp;
	while (tmp)
	{
		len = (ft_pos_in_string(tmp->var, '='));
		if (len > 0)
		{
			new_value = (char *) malloc(ft_strlen(tmp->var) + 3);
			len++;
			ft_copy(new_value, tmp->var, len + 1);
			ft_copy(&new_value[len], "\"", 0);
			ft_copy(&new_value[len + 1], &tmp->var[len], 0);
			len = ft_strlen(new_value);
			ft_copy(&new_value[len], "\"", 0);
			free(tmp->var);
			tmp->var = new_value;
		}
		tmp = tmp->next;
	}
}

t_envp	*ft_copy_envp_list(t_envp *envp)
{
	t_envp	*output;
	t_envp	*tmp;

	output = (ft_lstnew(envp->var));
	tmp = envp->next;
	while (tmp)
	{
		ft_lstadd_back(&output, ft_lstnew(tmp->var));
		tmp = tmp->next;
	}
	return (output);
}
