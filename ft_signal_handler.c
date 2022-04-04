/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 20:23:07 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/04 22:17:22 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_interactive_sigint(int sign)
{
	if (sign == SIGINT)
	{
		/*
		write(1,"\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		*/
	}
}

void	ft_bash_sigint(int sign)
{
	if (sign == SIGINT)
		g_ctrl_c = 1;
}

void	ft_child_crash(int sign)
{
	if (sign == SIGCHLD)
	{
		g_ctrl_c = 130;
		write(1,"\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		
		rl_redisplay();
	}
}
