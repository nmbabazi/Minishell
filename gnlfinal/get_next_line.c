/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 08:24:06 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/09/01 11:35:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char	*ft_write(int fd, char **line, char *temp, int *ret)
{
	int		i;
	int		j;
	char	buf[BUFFER_SIZE + 1];

	j = 0;
	i = 0;
	while (j == 0 && (*ret = read(fd, buf, BUFFER_SIZE)))
	{
		buf[*ret] = '\0';
		while (buf[i] && j == 0)
		{
			if (buf[i] == '\n')
			{
				temp = ft_substr_gnl(buf, i, BUFFER_SIZE - i);
				buf[i] = '\0';
				j++;
			}
			i++;
		}
		i = ft_creatline(buf, line);
	}
	return (temp);
}

char	*ft_long(char **line, char *temp, int *ret)
{
	if (*temp == '\n')
		temp++;
	if (*temp == '\n')
		*line = ft_substr_gnl(temp, 0, 0);
	else if (*temp != '\n')
		*line = ft_substr_gnl(temp, 0, ft_lenline(temp));
	while (temp && *temp != '\n')
		temp++;
	*ret = 1;
	return (temp);
}

char	*ft_short(int fd, char *temp, char **line, int *ret)
{
	if (temp == NULL)
	{
		*line = ft_substr_gnl("\0", 0, 0);
	}
	else if (ft_verifline(temp) == 0)
	{
		if (*temp == '\n')
			temp++;
		*line = ft_substr_gnl(temp, 0, ft_lenline(temp));
	}
	temp = ft_write(fd, line, temp, ret);
	return (temp);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	static char	*temp;
	char		buf[BUFFER_SIZE + 1];
	static char	*swp;

	ret = 0;
	if (fd < 0 || !line || BUFFER_SIZE < 1 || read(fd, buf, 0) < 0)
		return (-1);
	if (temp == NULL || ft_verifline(temp) == 0)
	{
		temp = ft_short(fd, temp, line, &ret);
		if (temp != NULL)
			free(swp);
		swp = temp;
	}
	else if (ft_verifline(temp) == 1)
		temp = ft_long(line, temp, &ret);
	if (ret)
		return (1);
	temp = NULL;
	swp = NULL;
	return (0);
}
