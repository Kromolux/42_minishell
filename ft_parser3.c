/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:07:15 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/07 15:56:13 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_do_valid_redirections(t_data *data, t_parser *parser)
{
	if (ft_strcmp(parser->token, "<"))
		return (ft_redirect_(data, parser, ft_redirect_in));
	else if (ft_strcmp(parser->token, ">"))
		return (ft_redirect_(data, parser, ft_redirect_out));
	else if (ft_strcmp(parser->token, "<<"))
		return (ft_redirect_prepare_in_in(data, parser));
	else if (ft_strcmp(parser->token, ">>"))
		return (ft_redirect_(data, parser, ft_redirect_out_out));
	else if (ft_strcmp(parser->token, "||"))
	{
		ft_print_error(parser->cmd, ERR_SYNTAX, parser->token);
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}

int	ft_redirect_(t_data *data, t_parser *parser,
	void (*redirect)(t_command *, char *))
{
	if (ft_check_next_token(data, parser) == RETURN_ERROR)
		return (RETURN_ERROR);
	redirect(parser->cmd, parser->token);
	return (RETURN_SUCCESS);
}

int	ft_check_next_token(t_data *data, t_parser *parser)
{
	free(parser->token);
	parser->token = ft_get_next_token(&parser->tmp, data);
	if (parser->token[0] == '\0' || ft_check_heredoc_end_term
		(parser->token) == RETURN_FALSE)
	{
		ft_print_error(parser->cmd, ERR_SYNTAX, parser->token);
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}

void	ft_inside_echo(t_parser *parser)
{
	parser->len = ft_len_whitespaces(parser->tmp);
	if (parser->len > 0)
	{
		parser->argc++;
		parser->cmd->argv[parser->argc] = ft_string_dup(" ");
		parser->tmp += parser->len;
	}
}

int	ft_redirect_prepare_in_in(t_data *data, t_parser *parser)
{
	if (ft_check_next_token(data, parser) == RETURN_ERROR)
		return (RETURN_ERROR);
	ft_set_parent_heredoc();
	ft_redirect_in_in(parser->cmd, parser->token);
	ft_set_parent_interactive();
	if (g_ctrl_c)
	{
		g_ctrl_c = 0;
		ft_delete_cmd(&data->c_line);
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}
