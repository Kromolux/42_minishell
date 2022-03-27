/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:57:38 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/27 20:48:08 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser(t_data *data)
{
	char	*tmp;
	char	*token;
	t_command	*cmd;
	int		len;
	int		argc;
	int		inside_echo;

	inside_echo = 0;
	argc = 0;
	data->c_line = ft_create_cmd_elem();
	cmd = data->c_line;
	tmp = data->r_line;
	tmp = ft_skip_whitespaces(tmp);
	while (*tmp)
	{
		len = ft_end_of_token(tmp, &inside_echo);
		//printf("len=%i\n", len);
		token = ft_get_substring(tmp, 0, len);
		//printf("token=%s\n", token);
		cmd->argv[argc] = ft_check_quotes_insert_var(token, data);
		free(token);
		//printf("argv=%s\n", data->c_line->argv[argc]);
		tmp += len;
		//printf("tmp=%s\n", tmp);
		if (inside_echo == 0)
			tmp = ft_skip_whitespaces(tmp);
		else
		{
			len = ft_len_whitespaces(tmp);
			if (len > 0)
			{
				argc++;
				cmd->argv[argc] = ft_get_substring(tmp, 0, 1);
				tmp += len;
			}
		}
		if (argc == 0 && ft_strcmp(cmd->argv[0], "echo"))
			inside_echo = 1;
		if (cmd->argv[argc][0] == '|')
		{
			cmd->next = ft_create_cmd_elem();
			cmd = cmd->next;
			argc = 0;
		}
		else
			argc++;
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

int	ft_end_of_token(char *s, int *inside_echo)
{
	int	i;
	int	s_quote;
	int	d_quote;
	int	found_quote;

	found_quote = 0;
	s_quote = 0;
	d_quote = 0;
	i = 0;
	while (s[i])
	{
		ft_check_quote(s[i], &d_quote, &s_quote);
		if (d_quote == 0 && s_quote == 0)
		{
			if (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
				break ;
			if (s[i] == '>' || s[i] == '<' || s[i] == '|')
			{
				*inside_echo = 0;
				break ;
			}
		}
		i++;
	}
	if (i == 0)
	{
		if (ft_strncmp(s, "<<", 2) == 0 || ft_strncmp(s, ">>", 2) == 0)
			return (2);
		else
			return (1);
	}
	return (i);
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
		if (input[check.i] == '\'')
			ft_inside_s_quote(&check, input);
		if (input[check.i] == '$')
		{
			ft_found_dollar(&check, input, data);
		}
		check.i++;
	}
	
	if (check.i_string == 0)
		return (ft_string_dup(input));
	return (ft_prepare_output(&check));
}