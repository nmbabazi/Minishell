/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:08:06 by dmontgen          #+#    #+#             */
/*   Updated: 2019/11/15 15:36:28 by dmontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;

	i = 0;
	while (dst[i] && dstsize > 0)
	{
		dstsize--;
		i++;
	}
	while (*src && dstsize > 1)
	{
		dst[i++] = *src++;
		dstsize--;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	while (*src++)
		i++;
	return (i);
}
