/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:57:38 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/05 17:11:28 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser(t_data *data)
{
	char		*tmp;
	char		*token;
	t_command	*cmd;
	int			len;
	int			argc;
	int			inside_echo;
	int			result;

	inside_echo = 0;
	result = 0;
	argc = 0;
	data->c_line = ft_create_cmd_elem();
	cmd = data->c_line;
	tmp = data->r_line;
	tmp = ft_skip_whitespaces(tmp);
	while (*tmp)
	{
		if (cmd->argv[argc] && cmd->argv[argc][0])
			argc++;
		len = ft_end_of_token(tmp, &inside_echo);
		token = ft_get_substring(tmp, 0, len);
		if (ft_strcmp(token, "|"))
		{
			tmp += len;
			free(token);
			token = ft_get_next_token(&tmp, data);
			if (token[0] == '\0')
			{
				ft_print_error(cmd, 1024, token);
				break ;
			}
		}
		result = ft_check_cmd(&cmd, &argc, token);
		if (ft_strcmp(token, "<"))
		{
			tmp += len;
			free(token);
			token = ft_get_next_token(&tmp, data);
			if (token[0] == '\0')
			{
				ft_print_error(cmd, 1024, token);
				break ;
			}
			ft_redirect_in(cmd, ft_get_next_token(&tmp, data));
		}
		else if (ft_strcmp(token, ">"))
		{
			tmp += len;
			free(token);
			token = ft_get_next_token(&tmp, data);
			if (token[0] == '\0')
			{
				ft_print_error(cmd, 1024, token);
				break ;
			}
			ft_redirect_out(cmd, ft_get_next_token(&tmp, data));
		}
		else if (ft_strcmp(token, "<<"))
		{
			tmp += len;
			free(token);
			token = ft_get_next_token(&tmp, data);
			if (token[0] == '\0' || !ft_check_heredoc_end_term(token))
			{
				ft_print_error(cmd, 1024, token);
				break ;
			}
			ft_set_parent_heredoc();
			ft_redirect_in_in(cmd, token);
			ft_set_parent_interactive();
			if (g_ctrl_c)
			{
				g_ctrl_c = 0;
				ft_delete_cmd(&data->c_line);
				break ;
			}
		}
		else if (ft_strcmp(token, ">>"))
		{
			tmp += len;
			free(token);
			token = ft_get_next_token(&tmp, data);
			if (token[0] == '\0' || !ft_check_heredoc_end_term(token))
			{
				ft_print_error(cmd, 1024, token);
				break ;
			}
			ft_redirect_out_out(cmd, ft_get_next_token(&tmp, data));
		}
		else if (ft_strcmp(token, "||"))
		{
			ft_print_error(cmd, 1024, token);
			break ;
		}
		if (result == 0)
			cmd->argv[argc] = ft_check_quotes_insert_var(token, data);
		free(token);
		if (result < 1)
			tmp += len;
		if (inside_echo == 0)
			tmp = ft_skip_whitespaces(tmp);
		else
		{
			len = ft_len_whitespaces(tmp);
			if (len > 0)
			{
				argc++;
				cmd->argv[argc] = ft_string_dup(" ");
				tmp += len;
			}
		}
		if (argc == 0 && ft_strcmp(cmd->argv[0], "echo"))
			inside_echo = 1;

	}
}

int	ft_check_heredoc_end_term(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] < 'a' || s[i] > 'z') && (s[i] < 'A' || s[i] > 'Z') && (s[i] < '0' || s[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_end_of_token(char *s, int *inside_echo)
{
	int	i;

	i = ft_find_end_of_token(s, inside_echo);
	if (i == 0)
	{
		if (ft_strncmp(s, "<<", 2) == 0 || ft_strncmp(s, ">>", 2) == 0
			|| ft_strncmp(s, "&&", 2) == 0 || ft_strncmp(s, "||", 2) == 0)
			return (2);
		else
			return (1);
	}
	return (i);
}

int	ft_find_end_of_token(char *s, int *inside_echo)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (s[i])
	{
		ft_check_quote(s[i], &d_quote, &s_quote);
		if (d_quote == 0 && s_quote == 0)
		{
			if (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
				break ;
			if (s[i] == '>' || s[i] == '<' || s[i] == '|' || s[i] == '&')
			{
				if (inside_echo)
					*inside_echo = 0;
				break ;
			}
		}
		i++;
	}
	return (i);
}
