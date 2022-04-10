/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 20:12:30 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 10:00:05 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_do_redirections(t_command *cmd, t_re *re)
{
	while (cmd)
	{
		re = cmd->re;
		while (re)
		{
			if (ft_strcmp(re->direct, "<"))
			{
				if (ft_redirect_(cmd, re, ft_redirect_in) == RETURN_ERROR)
					break ;
			}
			else if (ft_strcmp(re->direct, ">"))
			{
				if (ft_redirect_(cmd, re, ft_redirect_out) == RETURN_ERROR)
					break ;
			}
			else if (ft_strcmp(re->direct, ">>"))
			{
				if (ft_redirect_(cmd, re, ft_redirect_out_out) == RETURN_ERROR)
					break ;
			}
			re = re->next;
		}
		cmd = cmd->next;
	}
}
