/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 08:43:47 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/08 10:30:00 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (ft_string_dup(token));
	if (check.start != check.i)
		ft_lstadd_back(&check.str, ft_lstnew(&token[check.start]));
	return (ft_prepare_output(&check));
}
