/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:13:29 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/08 10:32:20 by rkaufman         ###   ########.fr       */
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

int	ft_redirect_in_in(t_data *data, t_command *cmd, char *end_term)
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_print_error(cmd, errno, NULL);
	if (cmd->re->in > 2)
		close(cmd->re->in);
	cmd->re->in = fd[0];
	if (ft_heredoc(data, fd[1], end_term) == RETURN_ERROR)
	{
		cmd->errnum = 1;
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
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

int	ft_heredoc(t_data *data, int fd_out, char *end_term)
{
	char	*user_input;
	char	*tmp;

	tmp = ft_realloc(end_term, "\n", 0, 0);
	while (1)
	{
		ft_write_fd(STDOUT_FILENO, "> ");
		user_input = ft_get_next_line(STDIN_FILENO);
		if (ft_strcmp(user_input, tmp))
			break ;
		user_input = ft_check_dollar_in_heredoc(user_input, data);
		ft_write_fd(fd_out, user_input);
		if (!user_input)
		{
			free((void *) tmp);
			close(fd_out);
			return (RETURN_ERROR);
		}
		free((void *) user_input);
	}
	free((void *) tmp);
	free((void *) user_input);
	close(fd_out);
	return (RETURN_SUCCESS);
}
