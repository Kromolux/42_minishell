/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 11:26:25 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/27 11:26:39 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_data *data)
{
	char	*output;

	output = (char *) malloc(BUFFER_SIZE);
	getcwd(output, BUFFER_SIZE);
	if (!output)
		return ;
	write(data->c_line->re->out, output, ft_strlen(output));
	write(data->c_line->re->out, "\n", 1);
	free(output);
}
