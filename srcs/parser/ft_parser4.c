/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 08:43:47 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 10:00:56 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_found_hash(char *input)
{
	input[0] = '\0';
	return (NULL);
}

void	ft_add_string(t_parse *check, char *input)
{
	char	*tmp;

	tmp = ft_get_substring(input, check->start, check->i - check->start);
	ft_lstadd_back(&check->str, ft_lstnew(tmp));
	free((void *) tmp);
	check->i_string++;
}

char	*ft_check_dollar_in_heredoc(char *token, t_data *data)
{
	t_parse	check;

	check.str = NULL;
	check.i = 0;
	check.i_string = 0;
	check.start = 0;
	while (token[check.i])
	{
		if (token[check.i] == '$')
			ft_found_dollar(&check, token, data);
		check.i++;
	}
	if (check.i_string == 0)
		return (token);
	if (check.start != check.i)
		ft_lstadd_back(&check.str, ft_lstnew(&token[check.start]));
	free(token);
	return (ft_prepare_output(check.str));
}

void	ft_questionmark(t_parse *check, t_data *data)
{
	char	*tmp2;

	tmp2 = ft_int_to_string((long) data->errnum);
	ft_lstadd_back(&check->str, ft_lstnew(tmp2));
	free((void *) tmp2);
}

t_return	ft_check_for_asterisk(t_parser *parser, char *input)
{
	if (ft_char_in_str(input, '*'))
	{
		ft_wildcard(parser->cmd, input);
		return (RETURN_TRUE);
	}
	ft_replace_in_string(input, (unsigned char) 255, '*');
	return (RETURN_FALSE);
}
