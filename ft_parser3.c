/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:07:15 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/06 16:52:16 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_do_valid_redirections(t_data *data, t_command *cmd, char *token, char **tmp, int len)
{
	if (ft_strcmp(token, "<"))
	{
		if (ft_check_next_token(data, cmd, *tmp + len) == RETURN_ERROR)
			return (RETURN_ERROR);
		*tmp += len;
		ft_redirect_in(cmd, ft_get_next_token(tmp, data));
	}
	else if (ft_strcmp(token, ">"))
	{
		if (ft_check_next_token(data, cmd, *tmp + len) == RETURN_ERROR)
			return (RETURN_ERROR);
		*tmp += len;
		ft_redirect_out(cmd, ft_get_next_token(tmp, data));
	}
	else if (ft_strcmp(token, "<<"))
	{
		if (ft_check_next_token(data, cmd, *tmp + len) == RETURN_ERROR)
			return (RETURN_ERROR);
		ft_set_parent_heredoc();
		*tmp += len;
		ft_redirect_in_in(cmd, ft_get_next_token(tmp, data));
		ft_set_parent_interactive();
		if (g_ctrl_c)
		{
			g_ctrl_c = 0;
			ft_delete_cmd(&data->c_line);
			return (RETURN_ERROR);
		}
	}
	else if (ft_strcmp(token, ">>"))
	{
		if (ft_check_next_token(data, cmd, *tmp + len) == RETURN_ERROR)
			return (RETURN_ERROR);
		*tmp += len;
		ft_redirect_out_out(cmd, ft_get_next_token(tmp, data));
	}
	else if (ft_strcmp(token, "||"))
	{
		ft_print_error(cmd, ERR_SYNTAX, token);
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}

int	ft_check_next_token(t_data *data, t_command *cmd, char *tmp)
{
	char	*new_token;

	new_token = ft_get_next_token(&tmp, data);
	if (new_token[0] == '\0' || !ft_check_heredoc_end_term(new_token))
	{
		ft_print_error(cmd, ERR_SYNTAX, new_token);
		free(new_token);
		return (RETURN_ERROR);
	}
	free(new_token);
	return (RETURN_SUCCESS);
}
