/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:02:37 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/26 19:36:00 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_data *data)
{
	(void) data;
}

int	ft_check_validity(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if ((argv[i] < 'A' || argv[i] > 'Z')
			&& (argv[i] < 'a' || argv[i] > 'z')
			&& (argv[i] < '0' || argv[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}
