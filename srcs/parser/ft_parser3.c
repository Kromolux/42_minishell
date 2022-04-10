/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:07:15 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 10:00:51 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_return	ft_do_valid_redirections(t_data *data)
{
	t_re		*re_tmp;
	t_command	*cmd_tmp;

	cmd_tmp = data->c_line;
	while (cmd_tmp)
	{
		re_tmp = cmd_tmp->re;
		while (re_tmp)
		{
			if (ft_strcmp(re_tmp->direct, "<<"))
				if (ft_redirect_prepare_in_in(data, cmd_tmp,
						re_tmp->file) == RETURN_ERROR)
					return (RETURN_ERROR);
			re_tmp = re_tmp->next;
		}
		cmd_tmp = cmd_tmp->next;
	}
	cmd_tmp = data->c_line;
	ft_do_redirections(cmd_tmp, re_tmp);
	return (RETURN_SUCCESS);
}

t_return	ft_redirect_(t_command *cmd, t_re *re,
	t_return (*redirect)(t_command *, t_re *))
{
	if (re->file[0] == '\0' || re->file[0] == '<' || re->file[0] == '>'
		|| re->file[0] == '|' || re->file[0] == '*')
	{
		cmd->result = RETURN_ERROR;
		ft_print_error(cmd, ERR_SYNTAX, re->file);
		return (RETURN_ERROR);
	}
	if (redirect(cmd, re) == RETURN_ERROR)
	{
		cmd->result = RETURN_ERROR;
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}

int	ft_check_next_token(t_command *cmd, char *file)
{
	if (file[0] == '\0' || ft_check_heredoc_end_term
		(file) == RETURN_FALSE)
	{
		ft_print_error(cmd, ERR_SYNTAX, file);
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}

void	ft_inside_echo(t_parser *parser)
{
	parser->len = ft_len_whitespaces(parser->tmp);
	if (parser->len > 0)
		parser->tmp += parser->len;
}

int	ft_redirect_prepare_in_in(t_data *data, t_command *cmd, char *end_term)
{
	if (ft_check_next_token(cmd, end_term) == RETURN_ERROR)
	{
		return (RETURN_ERROR);
	}
	ft_set_parent_heredoc();
	cmd->result = ft_redirect_in_in(data, cmd, end_term);
	ft_set_parent_interactive();
	if (cmd->result == RETURN_ERROR)
	{
		data->errnum = 1;
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}
