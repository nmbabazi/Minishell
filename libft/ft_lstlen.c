/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:59:59 by dmontgen          #+#    #+#             */
/*   Updated: 2020/09/15 18:40:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t  ft_lstlen(t_list *lst)
{
    t_list *iterator;
    size_t len;

    len = 0;
    iterator = lst;
    while (iterator)
    {
        iterator = iterator->next;
        len++;
    }
    return (len);
}