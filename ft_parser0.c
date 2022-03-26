/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:57:38 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/26 19:35:43 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser(t_data *data)
{
	char	*tmp;
	char	*token;
	int		len;
	int		pos;
	int		argc;

	argc = 0;
	pos = 0;
	data->c_line = ft_create_cmd_elem();
	tmp = data->r_line;
	tmp = ft_skip_whitespaces(tmp);
	while (*tmp)
	{
		len = ft_end_of_token(tmp);
		token = ft_get_substring(tmp, 0, len);
		data->c_line->argv[argc] = ft_check_quotes_insert_var(token, data->envp);
		tmp += len;
		tmp = ft_skip_whitespaces(tmp);
		argc++;
	}
}

char	*ft_skip_whitespaces(const char *s)
{
	while (*s != '\0' && (*s == ' ' || (*s >= '\t' && *s <= '\r')))
		s++;
	return ((char *)s);
}

int	ft_end_of_token(char *s)
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
		if (d_quote == 0 && s_quote == 0 && (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r')))
			break;
		i++;
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

char	*ft_check_quotes_insert_var(char *input, t_envp *envp)
{
	t_parse	check;

	check.i = 0;
	check.i_string = 0;
	check.start = 0;
	while (input[check.i])
	{
		if (input[check.i] == '\"')
			ft_inside_d_quote(&check, input, envp);
		if (input[check.i] == '\'')
			ft_inside_s_quote(&check, input);
		if (input[check.i] == '$')
			ft_found_dollar(&check, input, envp);
		check.i++;
	}
	if (check.i_string == 0)
		return (ft_string_dup(input));
	return (ft_prepare_output(&check));
}


