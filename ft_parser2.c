/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 07:51:02 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/07 09:55:58 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_cmd(t_data *data, t_parser *parser)
{
	parser->tmp += parser->len;
	if (parser->token[0] == '|')
	{
		free((void *) parser->token);
		parser->token = ft_get_next_token(&parser->tmp, data);
		if (parser->token[0] == '\0'
			|| !ft_check_heredoc_end_term(parser->token))
		{
			ft_print_error(parser->cmd, ERR_SYNTAX, parser->token);
			return (RETURN_ERROR);
		}
		parser->cmd->next = ft_create_cmd_elem();
		parser->cmd = parser->cmd->next;
		parser->cmd->argv[0] = ft_string_dup(parser->token);
		parser->argc = 1;
		return (RETURN_SUCCESS);
	}
	if (ft_strcmp(parser->token, "<") || (ft_strcmp(parser->token, ">"))
		|| (ft_strcmp(parser->token, "<<")) || (ft_strcmp(parser->token, ">>")))
		return (RETURN_TRUE);
	return (RETURN_FALSE);
}

void	ft_check_quote(char c, int *d_quote, int *s_quote)
{
	if (c == '\"')
	{
		if (*d_quote == 0)
			*d_quote = 1;
		else
			*d_quote = 0;
	}
	else if (c == '\'')
	{
		if (*s_quote == 0)
			*s_quote = 1;
		else
			*s_quote = 0;
	}
}

int	ft_len_whitespaces(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r')))
		i++;
	return (i);
}

char	*ft_skip_whitespaces(const char *s)
{
	while (*s != '\0' && (*s == ' ' || (*s >= '\t' && *s <= '\r')))
		s++;
	return ((char *)s);
}

char	*ft_check_quotes_insert_var(char *input, t_data *data)
{
	t_parse	check;

	check.i = 0;
	check.i_string = 0;
	check.start = 0;
	while (input[check.i])
	{
		if (input[check.i] == '\"')
			ft_inside_d_quote(&check, input, data);
		else if (input[check.i] == '\'')
			ft_inside_s_quote(&check, input);
		else if (input[check.i] == '$')
			ft_found_dollar(&check, input, data);
		check.i++;
	}
	if (check.i_string == 0)
		return (ft_string_dup(input));
	if (check.start != check.i)
	{
		check.string[check.i_string] = ft_string_dup(&input[check.start]);
		check.i_string++;
	}
	return (ft_prepare_output(&check));
}
