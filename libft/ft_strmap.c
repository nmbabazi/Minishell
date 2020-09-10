/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 18:54:51 by dmontgen          #+#    #+#             */
/*   Updated: 2019/11/07 16:20:02 by dmontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = NULL;
	if (s && f)
	{
		if (!(newstr = (char *)malloc(sizeof(*newstr) * (ft_strlen(s) + 1))))
			return (NULL);
		while (s[i])
		{
			newstr[i] = f(s[i]);
			i++;
		}
		newstr[i] = '\0';
	}
	return (newstr);
}
