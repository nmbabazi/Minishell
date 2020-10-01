/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:51:13 by user42            #+#    #+#             */
/*   Updated: 2020/10/01 13:07:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_get_var(t_list *list, char *var)
{
	t_list	*next;

	while (list)
	{
		next = list->next;
		if (ft_strncmp(list->content, var, ft_strlen(var)) == 0)
		{
			return (ft_substr(list->content, ft_strlen(var),
			ft_strlen(list->content) - ft_strlen(var)));
		}
		list = next;
	}
	return (NULL);
}

int		ft_surch_var(t_list *list, char *var)
{
	t_list	*next;
	char	*str;
	int		len_var;
	int		len_content;

	len_content = 0;
	len_var = ft_strlen(var);
	if (ft_strchr(var, '='))
		len_var--;
	while (list)
	{
		next = list->next;
		str = list->content;
		while (str[len_content] != '=' && str[len_content])
			len_content++;
		if (ft_strncmp(list->content, var, len_var) == 0 &&
				len_var == len_content)
			return (1);
		list = next;
		len_content = 0;
	}
	return (0);
}
