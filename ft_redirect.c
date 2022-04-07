/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:13:29 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/07 10:11:05 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect_in(t_command *cmd, char *filename)
{
	if (cmd->re->in > 2)
		close(cmd->re->in);
	cmd->re->in = open(filename, O_RDONLY);
	if (cmd->re->in < 0)
		ft_print_error(cmd, errno, filename);
}

void	ft_redirect_in_in(t_command *cmd, char *end_term)
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_print_error(cmd, errno, NULL);
	if (cmd->re->in > 2)
		close(cmd->re->in);
	ft_heredoc(fd[1], end_term);
	cmd->re->in = fd[0];
}

void	ft_redirect_out(t_command *cmd, char *filename)
{
	if (cmd->re->out > 2)
		close(cmd->re->out);
	cmd->re->out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, FILE_RIGHTS);
	if (cmd->re->out < 0)
		ft_print_error(cmd, errno, NULL);
}

void	ft_redirect_out_out(t_command *cmd, char *filename)
{
	if (cmd->re->out > 2)
		close(cmd->re->out);
	cmd->re->out = open(filename, O_CREAT | O_WRONLY | O_APPEND, FILE_RIGHTS);
	if (cmd->re->out < 0)
		ft_print_error(cmd, errno, NULL);
}

void	ft_heredoc(int fd_out, char *end_term)
{
	char	*user_input;
	char	*tmp;
	int		signal;

	signal = 0;
	tmp = ft_realloc(end_term, "\n", 0, 0);
	while (1)
	{
		if (signal == 0)
			ft_write_fd(STDOUT_FILENO, "> ");
		user_input = ft_get_next_line(STDIN_FILENO);
		if (ft_strcmp(user_input, tmp) || g_ctrl_c)
			break ;
		ft_write_fd(fd_out, user_input);
		if (!user_input)
			signal = 1;
		else
			signal = 0;
		free((void *) user_input);
	}
	free((void *) tmp);
	free((void *) user_input);
	close(fd_out);
}
