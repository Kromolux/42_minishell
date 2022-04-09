/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 09:00:38 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/09 09:42:09 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int	i;
	
	(void) argc;
	(void) envp;
	i = 0;
	while (i < argc)
	{
		printf("argc=[%2i]=[%s]\n", i, argv[i]);
		i++;
	}
	return (0);
}
