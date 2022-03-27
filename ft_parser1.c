/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:26:10 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/27 14:35:25 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_inside_d_quote(t_parse *check, char *input, t_data *data)
{
	if (check->i > 0)
	{
		check->string[check->i_string] = ft_get_substring(input, 0, check->i - check->start);
		check->i_string++;
	}
	check->start = check->i + 1;
	check->i++;
	while (input[check->i])
	{
		if (input[check->i] == '$')
			ft_found_dollar(check, input, data);
		if (input[check->i] == '\"')
		{
			check->string[check->i_string] = ft_get_substring(input, check->start, check->i - check->start);
			check->i_string++;
			break ;
		}
		check->i++;
	}
}

void	ft_inside_s_quote(t_parse *check, char *input)
{
	if (check->i > 0)
	{
		check->string[check->i_string] = ft_get_substring(input, 0, check->i - check->start);
		check->i_string++;
	}
	check->start = check->i + 1;
	check->i++;
	while (input[check->i])
	{
		if (input[check->i] == '\'')
		{
			check->string[check->i_string] = ft_get_substring(input, check->start, check->i - check->start);
			check->i_string++;
			break ;
		}
		check->i++;
	}
}

void	ft_found_dollar(t_parse *check, char *input, t_data *data)
{
	char	*tmp;
	
	check->string[check->i_string] = ft_get_substring(input, check->start,
		check->i - check->start);
	check->i_string++;
	tmp = ft_get_var(&input[check->i + 1]);
	if (ft_strncmp(tmp, "?", 1) == 0)
		check->string[check->i_string] = ft_int_to_string(data->errnum);
	else
		check->string[check->i_string] = ft_string_dup(ft_getenv(tmp, data->envp));
	check->i_string++;
	check->i += ft_strlen(tmp);
	check->start = check->i + 1;
	free(tmp);
}

char	*ft_prepare_output(t_parse *check)
{
	char	*output;
	int		i;

	output = (char *) malloc(1);
	output[0] = '\0';
	i = 0;
	while (i < check->i_string)
	{
		output = ft_realloc(output, check->string[i], 1, 1);
		i++;
	}
	return (output);
}