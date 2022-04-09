/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 17:49:37 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/09 17:49:45 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_replace_in_string(char *s, char c_replace, char c_with)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == c_replace)
		{
			*s = c_with;
			count++;
		}
		s++;
	}
	return (count);
}
