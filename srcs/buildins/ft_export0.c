/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:02:37 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 09:58:43 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_export(t_data *data, t_command *cmd)
{
	t_envp	*tmp;

	if (!cmd->argv)
		ft_var_printing(data);
	tmp = cmd->argv;
	while (tmp)
	{
		if (!ft_check_validity(tmp->var))
		{
			ft_print_error(cmd, ERR_NOT_VALID, tmp->var);
		}
		else if (cmd == data->c_line)
			ft_change_envp(data, tmp->var);
		tmp = tmp->next;
	}
	return (RETURN_SUCCESS);
}

void	ft_change_envp(t_data *data, char *var)
{
	t_envp	*tmp;

	tmp = ft_get_envp_element(data->envp, var);
	if (tmp)
	{
		free((void *) tmp->var);
		tmp->var = ft_string_dup(var);
	}
	else
		ft_lstadd_back(&data->envp, ft_lstnew(var));
}

int	ft_check_validity(char *argv)
{
	int	i;

	i = 0;
	if ((argv[0] >= '0' && argv[0] <= '9') || argv[0] == '=')
		return (0);
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
		ft_write_fd(data->c_line->fd->out, EXPORT);
		ft_write_fd_nl(data->c_line->fd->out, tmp->var);
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
			equation = ft_strncmp(tmp->var, tmp->next->var,
					ft_pos_in_string(tmp->var, '='));
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
