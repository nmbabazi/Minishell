/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:49:48 by dmontgen          #+#    #+#             */
/*   Updated: 2019/11/15 15:18:33 by dmontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char *pdest;
	unsigned char *psrc;

	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	while (n)
	{
		*pdest = *psrc;
		if (*psrc == (unsigned char)c)
			return (pdest + 1);
		pdest++;
		psrc++;
		n--;
	}
	return (0);
}
