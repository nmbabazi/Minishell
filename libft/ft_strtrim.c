/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:27:12 by dmontgen          #+#    #+#             */
/*   Updated: 2019/11/11 10:44:26 by dmontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_space_before(char const *str, char const *set)
{
	int i;
	int j;
	int l;

	i = 0;
	j = 0;
	while (str[i])
	{
		l = 0;
		while (set[j])
		{
			if (str[i] == set[j])
				l++;
			j++;
		}
		if (l == 0)
			return (i);
		i++;
		j = 0;
	}
	return (i);
}

static	int		ft_space_after(char const *str, char const *set)
{
	int i;
	int j;
	int l;

	i = ft_strlen(str) - 1;
	j = 0;
	while (i >= 0)
	{
		l = 0;
		while (set[j])
		{
			if (str[i] == set[j])
				l++;
			j++;
		}
		if (l == 0)
			return (i + 1);
		i--;
		j = 0;
	}
	return (0);
}

char			*ft_strtrim(char const *s, char const *set)
{
	int		before;
	int		after;
	char	*newstr;

	if (!s || !set)
		return (NULL);
	before = ft_space_before(s, set);
	after = ft_space_after(s, set);
	newstr = NULL;
	if ((after - before) <= 0)
	{
		newstr = malloc(1);
		newstr[0] = '\0';
		return (newstr);
	}
	if (!(newstr = ft_strnew(after - before)))
		return (NULL);
	ft_strncpy(newstr, (s + before), (after - before));
	return (newstr);
}
