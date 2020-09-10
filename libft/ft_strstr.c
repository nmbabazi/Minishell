/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:40:22 by dmontgen          #+#    #+#             */
/*   Updated: 2019/11/06 18:40:41 by dmontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (needle[k])
		k++;
	while (haystack[i])
	{
		while (needle[j] && haystack[i + j] == needle[j])
		{
			j++;
			if (j == k)
				return ((char *)haystack + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
