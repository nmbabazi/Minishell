/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:59:59 by dmontgen          #+#    #+#             */
/*   Updated: 2020/09/12 19:25:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *tmp;
	t_list *next;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		del(tmp->content);
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}
