/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:59:59 by dmontgen          #+#    #+#             */
/*   Updated: 2020/09/09 11:49:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static  char	*ft_cdup(char c)
{
	int		i;
	char	*new_string;

	i = 0;
	if (!(new_string = malloc(sizeof(char) * (2))))
		return (0);
	new_string[i] = c;
		i++;
	new_string[i] = '\0';
	return (new_string);
}

t_list          *ft_str_to_list(t_list **lst, char *str)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (str[i])
	{
		if (!(temp = malloc(sizeof(t_list))))
			return (NULL);
		if (!(temp->content = ft_cdup(str[i])))
			return (NULL);
		temp->next = 0;
		ft_lstadd_back(lst, temp);
		i++;
	}
	return (*lst);
}