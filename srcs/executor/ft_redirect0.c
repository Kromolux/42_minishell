/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:13:29 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 10:00:01 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_return	ft_redirect_in(t_command *cmd, t_re *re)
{
	if (!re->next)
	{
		if (cmd->fd->in > 2)
			close(cmd->fd->in);
		cmd->fd->in = open(re->file, O_RDONLY);
		if (cmd->fd->in < 0)
		{
			ft_print_error(cmd, ERR_FD, re->file);
			return (RETURN_ERROR);
		}
	}
	else if (access(re->file, R_OK) == RETURN_ERROR)
	{
		ft_print_error(cmd, ERR_FD, re->file);
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}

t_return	ft_redirect_in_in(t_data *data, t_command *cmd, char *end_term)
{
	int	fd[2];

	if (pipe(fd) == RETURN_ERROR)
		ft_print_error(cmd, errno, NULL);
	if (cmd->fd->in > 2)
		close(cmd->fd->in);
	cmd->fd->in = fd[0];
	if (ft_heredoc(data, fd[1], end_term) == RETURN_ERROR)
	{
		cmd->errnum = 1;
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}

t_return	ft_redirect_out(t_command *cmd, t_re *re)
{
	if (cmd->fd->out > 2)
		close(cmd->fd->out);
	cmd->fd->out = open(re->file, O_CREAT | O_WRONLY | O_TRUNC, FILE_RIGHTS);
	if (cmd->fd->out < 0)
	{
		ft_print_error(cmd, errno, NULL);
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}

t_return	ft_redirect_out_out(t_command *cmd, t_re *re)
{
	if (cmd->fd->out > 2)
		close(cmd->fd->out);
	cmd->fd->out = open(re->file, O_CREAT | O_WRONLY | O_APPEND, FILE_RIGHTS);
	if (cmd->fd->out < 0)
	{
		ft_print_error(cmd, errno, NULL);
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
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
		if (!user_input)
		{
			free((void *) tmp);
			close(fd_out);
			return (RETURN_ERROR);
		}
		user_input = ft_check_dollar_in_heredoc(user_input, data);
		if (ft_strcmp(user_input, tmp))
			break ;
		ft_write_fd(fd_out, user_input);
		free((void *) user_input);
	}
	free((void *) tmp);
	free((void *) user_input);
	close(fd_out);
	return (RETURN_SUCCESS);
}
