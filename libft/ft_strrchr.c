/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:06:52 by dmontgen          #+#    #+#             */
/*   Updated: 2019/11/15 15:27:21 by dmontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *temp;

	temp = 0;
	while (*s)
	{
		if (*s == c)
			temp = (char *)s;
		s++;
	}
	if (*s == c)
		temp = (char *)s;
	return (temp);
}
