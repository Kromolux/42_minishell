/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:49:25 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/27 11:51:13 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_error(t_data *data)
{
	write(data->c_line->re->err, PROMPT, ft_strlen(PROMPT));
	write(data->c_line->re->err, data->c_line->argv[0],
		ft_strlen(data->c_line->argv[0]));
	if (data->errnum == 127)
		write(data->c_line->re->err, ": command not found\n", 20);
	return (data->errnum);
}
