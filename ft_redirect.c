/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:13:29 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/31 17:16:33 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect_in(t_command *cmd, char *filename)
{
	t_redirect	*tmp;

	if (cmd->re->in == STDIN_FILENO || cmd->re->in < -1)
	{
		cmd->re->in = open(filename, O_RDONLY);
		if (cmd->re->in < 0)
			ft_print_error(cmd, errno);
	}
	else if (cmd->re->in >= 0)
	{
		//loop through list and create new element
		tmp = cmd->re;
		while (tmp->next)
		{
			tmp = tmp->next;
			if (tmp->in == -1)
			{
				tmp->in = open(filename, O_RDONLY);
				if (cmd->re->in < 0)
					ft_print_error(cmd, errno);
				return ;
			}
		}
		tmp->next = ft_create_re();
		tmp->in = open(filename, O_RDONLY);
		if (cmd->re->in < 0)
			ft_print_error(cmd, errno);
	}
}

void	ft_redirect_out(t_command *cmd, char *filename)
{
	t_redirect	*tmp;

	if (cmd->re->out == STDOUT_FILENO || cmd->re->out < -1)
	{
		cmd->re->out = open(filename, O_CREAT | O_WRONLY);
		if (cmd->re->out< 0)
			ft_print_error(cmd, errno);
	}
	else if (cmd->re->out >= 0)
	{
		//loop through list and create new element
		tmp = cmd->re;
		while (tmp->next)
		{
			tmp = tmp->next;
			if (tmp->out == -1)
			{
				tmp->out = open(filename, O_CREAT | O_WRONLY);
				if (cmd->re->out < 0)
					ft_print_error(cmd, errno);
				return ;
			}
		}
		tmp->next = ft_create_re();
		tmp->out = open(filename, O_CREAT | O_WRONLY);
		if (cmd->re->out < 0)
			ft_print_error(cmd, errno);
	}
}

t_redirect *ft_create_re(void)
{
	t_redirect *output;

	output = (t_redirect *) malloc(sizeof(t_redirect));
	if (!output)
		return (NULL);
	output->in = -1;
	output->out = -1;
	output->err = -1;
	output->next = NULL;
	return (output);
}
