/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:02:37 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/01 21:37:47 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_data *data, t_command *cmd)
{
	int	i;

	i = 1;
	if (!cmd->argv[1])
		ft_var_printing(data);
	while (cmd->argv[i])
	{
		if (!ft_check_validity(cmd->argv[i]))
		{
			data->errnum = 1;
			return (ft_print_error(cmd, 999));
		}
		ft_change_envp(data, cmd->argv[i]);
		i++;
	}
	return (0);
}

void	ft_change_envp(t_data *data, char *var)
{
	t_envp	*tmp;

	tmp = ft_get_envp_element(data->envp, var);
	if (tmp)
	{
		free(tmp->var);
		tmp->var = ft_string_dup(var);
	}
	else
		ft_lstadd_back(&data->envp, ft_lstnew(var));
}

int	ft_check_validity(char *argv)
{
	int	i;

	i = 0;
	//printf("entered check validity [%s]\n", argv);
	if (argv[0] >= '0' && argv[0] <= '9')
	{
		//printf("invalid!\n");
		return (0);
	}
	while (argv[i] && argv[i] != '=')
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

	copy = ft_copy_envp_list(data->envp);
	ft_add_quotes(copy);
	ft_sort_list(&copy);
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

void	ft_sort_list(t_envp **envp)
{
	t_envp	*tmp;
	int		sorted;
	int		equation;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		tmp = *envp;
		while (tmp && tmp->next)
		{
			equation = ft_strncmp(tmp->var, tmp->next->var, ft_pos_in_string(tmp->var, '='));
			if (equation > 0)
			{
				ft_swap(envp, tmp);
				sorted = 0;
			}
			else
				tmp = tmp->next;
		}
	}
}
