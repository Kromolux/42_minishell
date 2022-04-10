/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:01:44 by rkaufman          #+#    #+#             */
/*   Updated: 2022/04/10 10:00:03 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_re	*ft_lstnew_re(char *direct, char *file)
{
	t_re	*new_element;

	new_element = (t_re *) malloc(sizeof(t_re));
	if (!new_element)
		return (NULL);
	new_element->direct = ft_string_dup(direct);
	new_element->file = ft_string_dup(file);
	new_element->next = NULL;
	return (new_element);
}

t_re	*ft_lstlast_re(t_re *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_re(t_re **lst, t_re *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast_re(*lst)->next = new;
}

void	ft_lstdel_re(t_re **re)
{
	t_re	*re_tmp;

	while (*re)
	{
		re_tmp = *re;
		*re = (*re)->next;
		free((void *) re_tmp->direct);
		free((void *) re_tmp->file);
		re_tmp->direct = NULL;
		re_tmp->file = NULL;
		free((void *) re_tmp);
		re_tmp = NULL;
	}
	*re = NULL;
}

void	ft_get_re(t_data *data, t_parser *parser)
{
	char	*file;
	char	*direct;

	direct = parser->token;
	parser->token = NULL;
	file = ft_get_next_token(parser, data);
	ft_lstadd_back_re(&parser->cmd->re, ft_lstnew_re(direct, file));
	free((void *) direct);
	free((void *) file);
}
