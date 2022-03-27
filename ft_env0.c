/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 18:41:59 by rkaufman          #+#    #+#             */
/*   Updated: 2022/03/27 20:46:34 by rkaufman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_copy_envp(char **envp)
{
	t_envp	*output;
	int		i;

	output = ft_lstnew(envp[0]);
	i = 1;
	while (envp[i])
	{
		ft_lstadd_back(&output, ft_lstnew(envp[i]));
		i++;
	}
	return (output);
}

t_envp	*ft_lstnew(char *content)
{
	t_envp	*new_element;

	new_element = (t_envp *) malloc(sizeof(t_envp));
	if (!new_element)
		return (NULL);
	new_element->var = ft_get_substring(content, 0, ft_strlen(content));
	new_element->next = NULL;
	return (new_element);
}

t_envp	*ft_lstlast(t_envp *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_envp **lst, t_envp *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;

}

void	ft_delete_list(t_envp **lst)
{
	t_envp	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->var);
		free(tmp);
	}
	*lst = NULL;
}

char	*ft_getenv(char *var, t_envp *envp_list)
{
	while (!ft_str_var_cmp(var, envp_list->var))
	{
		envp_list = envp_list->next;
		if (envp_list == NULL)
			return (NULL);
	}
	return (&envp_list->var[ft_pos_in_string(envp_list->var, '=') + 1]);
}
