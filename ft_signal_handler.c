/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 20:23:07 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/06 15:48:09 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parent_interactive_sigint(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_parent_active_sigint(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		g_ctrl_c = 1;
	}
}

void	ft_parent_active_sigquit(int sign)
{
	if (sign == SIGQUIT)
	{
		ft_write_fd(1, "Quit\n");
	}
}

void	ft_bash_sigint(int sign)
{
	if (sign == SIGINT)
		g_ctrl_c = 1;
}

/*
	sigemptyset(&data->response.sa_mask);
	//sigaddset(&data->response.sa_mask, SIGCHLD);
	data->response.sa_flags = SA_SIGINFO;
	data->response.sa_handler = &ft_interactive_sigint;
	sigaction(SIGINT, &data->response, NULL);
	sigemptyset(&data->child.sa_mask);
	data->child.sa_handler = &ft_active_sigquit;
	data->child.sa_flags = SA_SIGINFO;
	//sigaction(SIGCHLD, &data->child, NULL);
	*/

	/*
	data->response.sa_handler = &ft_active_sigint;
	sigaction(SIGINT, &data->response, NULL);
	sigaction(SIGQUIT, &data->child, NULL);
	*/
	//sigaction(SIGINT, SIG_DFL, NULL);
	//sigaction(SIGQUIT, SIG_DFL, NULL);