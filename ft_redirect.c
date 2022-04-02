/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:13:29 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/01 21:42:32 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect_in(t_command *cmd, char *filename)
{
	if (cmd->re->in > 2)
		close(cmd->re->in);
	cmd->re->in = open(filename, O_RDONLY);
	if (cmd->re->in < 0)
		ft_print_error(cmd, errno);
	free(filename);
}

void	ft_redirect_in_in(t_command *cmd, char *end_term)
{
	int	fd[2];

	(void) end_term;
	if (pipe(fd) == -1)
		ft_print_error(cmd, errno);
	if (cmd->re->in > 2)
		close(cmd->re->in);
	ft_heredoc(fd[1], end_term);
	cmd->re->in = fd[0];
	free(end_term);
}

void	ft_redirect_out(t_command *cmd, char *filename)
{
	if (cmd->re->out > 2)
		close(cmd->re->out);
	cmd->re->out = open(filename, O_CREAT | O_WRONLY | O_TRUNC, FILE_RIGHTS);
	if (cmd->re->out< 0)
		ft_print_error(cmd, errno);
	free(filename);
}

void	ft_redirect_out_out(t_command *cmd, char *filename)
{
	if (cmd->re->out > 2)
		close(cmd->re->out);
	cmd->re->out = open(filename, O_CREAT | O_WRONLY | O_APPEND, FILE_RIGHTS);
	if (cmd->re->out < 0)
		ft_print_error(cmd, errno);
	free(filename);
}

void	ft_heredoc(int fd_out, char *end_term)
{
	char	*user_input;
	char	*tmp;
	int		signal;

	sigaction(SIGINT, NULL, NULL);
	sigaction(SIGQUIT, NULL, NULL);
	signal = 0;
	//printf("entered heredoc with fd=[%i] and end_term=[%s]\n", fd_out, end_term);
	while (1)
	{
		if (signal == 0)
			write(1, "> ", 2);
		user_input = ft_get_next_line(0);
		tmp = ft_remove_char(ft_string_dup(user_input), '\n');
		//printf("result after remove_char [%s]\n", tmp);
		if (ft_strcmp(tmp, end_term) || g_ctrl_c)
			break ;
		write(fd_out, user_input, ft_strlen(user_input));
		if (!user_input)
			signal = 1;
		else
			signal = 0;
		//printf("after write\n");
		free(user_input);
		//printf("after first free\n");
		free(tmp);
		//printf("after second free\n");
	}
	free(tmp);
	free(user_input);
	close(fd_out);
}
