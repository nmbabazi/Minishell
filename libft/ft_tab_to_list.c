/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:59:59 by dmontgen          #+#    #+#             */
/*   Updated: 2020/09/09 11:48:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_tab_to_list(t_list **lst, char **tab)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (tab[i])
	{
		if (!(temp = malloc(sizeof(t_list))))
			return (NULL);
		if (!(temp->content = ft_strdup(tab[i])))
			return (NULL);
		temp->next = 0;
		ft_lstadd_back(lst, temp);
		i++;
	}
	return (*lst);
}
