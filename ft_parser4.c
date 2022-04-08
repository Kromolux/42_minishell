/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 08:43:47 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/08 10:04:15 by rkaufman         ###   ########.fr       */
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
