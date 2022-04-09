/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 09:00:38 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/09 13:20:36 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h> 
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

	DIR				*d;
	struct dirent	*dir;

	d = opendir(".");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
	return (0);
}
