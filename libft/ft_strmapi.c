/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:51:42 by dmontgen          #+#    #+#             */
/*   Updated: 2019/11/12 16:09:03 by dmontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = NULL;
	if (!s)
		return (NULL);
	if (s && f)
	{
		if (!(newstr = (char *)malloc(sizeof(*newstr) * ft_strlen(s) + 1)))
			return (NULL);
		while (s[i])
		{
			newstr[i] = f(i, s[i]);
			i++;
		}
		newstr[i] = '\0';
	}
	return (newstr);
}
