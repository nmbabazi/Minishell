/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:59:59 by dmontgen          #+#    #+#             */
/*   Updated: 2020/09/22 13:23:41 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *tmp;

	if (!alst)
		return ;
	if (*alst)
		tmp = *alst;
	else
	{
		*alst = new;
		return ;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}
