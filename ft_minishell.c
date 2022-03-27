/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 09:17:33 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/27 20:06:48 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data		data;

	(void) argc;
	(void) argv;
	data.envp = ft_copy_envp(envp);
	while (1)
	{
		data.r_line = readline(PROMPT);
		if (ft_strlen(data.r_line) > 0)
			add_history(data.r_line);
		ft_parser(&data);
		if (data.c_line->argv[0] && data.c_line->argv[0][0])
		{
			ft_print_commands(data.c_line);
			if (ft_build_in_exe(&data))
				break ;
		}
		//ft_execev_fork...
		free(data.r_line);
		ft_delete_cmd(data.c_line);
	}
	ft_delete_list(&data.envp);
	ft_delete_cmd(data.c_line);
	free(data.r_line);
	return (0);
}
