/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststring_to_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:59:59 by dmontgen          #+#    #+#             */
/*   Updated: 2020/09/15 18:39:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    **ft_lststring_to_tab(t_list *lst)
{
    char **str;
    t_list *iterator;
    int i;

    i = 0;
    iterator = lst;
    if(!(str = (char **)malloc(sizeof(char*) * ft_lstlen(lst) + 1)))
        return (NULL);
    while (iterator)
    {
        str[i] = ft_strdup(iterator->content);
        iterator = iterator->next;
        i++;
    }
    str[i] = NULL;
    return (str);
}