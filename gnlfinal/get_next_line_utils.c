/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 08:26:11 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/01 11:38:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_verifline(char *str)
{
	int i;

	i = 0;
	if (str[i] == '\n')
		i++;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int		ft_lenline(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		size;
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = ft_lenline(s1) + ft_lenline(s2);
	if (!s1 || !s2)
		return (0);
	if (!(p = malloc(sizeof(char) * (size + 1))))
		return (0);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		p[i] = s2[j];
		j++;
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;
	char	*call;

	i = 0;
	call = "\0";
	if (!s)
		return (0);
	if (start > (unsigned int)ft_lenline(s))
		return (call);
	if (!(p = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (s[start] && i < len)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}

int		ft_creatline(char *buf, char **line)
{
	char *swp;

	if (!*line)
		*line = ft_substr_gnl(buf, 0, ft_lenline(buf));
	else
	{
		swp = *line;
		*line = ft_strjoin_gnl(*line, buf);
		free(swp);
	}
	return (0);
}
