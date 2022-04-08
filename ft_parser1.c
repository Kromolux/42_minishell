/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:26:10 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/08 10:19:52 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_inside_d_quote(t_parse *check, char *input, t_data *data)
{
	if (check->i > 0)
		ft_add_string(check, input);
	check->start = check->i + 1;
	check->i++;
	while (input[check->i])
	{
		if (input[check->i] == '$')
			ft_found_dollar(check, input, data);
		if (input[check->i] == '\"')
		{
			ft_add_string(check, input);
			check->start = check->i + 1;
			break ;
		}
		check->i++;
	}
}

void	ft_inside_s_quote(t_parse *check, char *input)
{
	if (check->i > 0)
		ft_add_string(check, input);
	check->start = check->i + 1;
	check->i++;
	while (input[check->i])
	{
		if (input[check->i] == '\'')
		{
			ft_add_string(check, input);
			check->start = check->i + 1;
			break ;
		}
		check->i++;
	}
}

void	ft_found_dollar(t_parse *check, char *input, t_data *data)
{
	char	*tmp;
	char	*tmp2;

	ft_add_string(check, input);
	tmp = ft_get_var(&input[check->i + 1]);
	if (ft_strncmp(tmp, "?", 1) == 0)
	{
		tmp2 = ft_int_to_string((long) data->errnum);
		ft_lstadd_back(&check->str, ft_lstnew(tmp2));
		free((void *) tmp2);
	}
	else if (ft_strncmp(&input[check->i + 1], "\0", 1) == 0
		|| ft_strncmp(&input[check->i + 1], "\'", 1) == 1
		|| ft_strncmp(&input[check->i + 1], "\"", 1) == 1)
		ft_lstadd_back(&check->str, ft_lstnew("$"));
	else
	{
		ft_lstadd_back(&check->str, ft_lstnew(ft_getenv(tmp, data->envp)));
	}
	check->i_string++;
	check->i += ft_strlen(tmp);
	check->start = check->i + 1;
	free((void *) tmp);
}

char	*ft_prepare_output(t_parse *check)
{
	char	*output;

	output = (char *) malloc(1);
	output[0] = '\0';
	while (check->str)
	{
		output = ft_realloc(output, check->str->var, 1, 0);
		check->str = check->str->next;
	}
	ft_delete_list(&check->str);
	return (output);
}

char	*ft_get_next_token(t_parser *parser, t_data *data)
{
	char	*output;
	int		len;

	parser->tmp = ft_skip_whitespaces(parser->tmp);
	len = ft_end_of_token(parser->tmp, 0);
	parser->token = ft_get_substring(parser->tmp, 0, len);
	output = ft_check_quotes_insert_var(parser, data);
	parser->tmp += len;
	return (output);
}
