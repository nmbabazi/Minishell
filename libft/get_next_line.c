/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejawe <ejawe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:17:42 by dmontgen          #+#    #+#             */
/*   Updated: 2020/10/21 22:40:30 by ejawe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/minishell.h"

#include <stdio.h>

char	*create_last_str(char *str, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	*line = ft_substr(str, 0, i);
	if (ft_strchr(str, '\n') != NULL)
	{
		temp = str;
		str = ft_strdup(ft_strchr(str, '\n'));
		free(temp);
	}
	else if (ft_strchr(str, '\0') != NULL)
	{
		temp = str;
		str = ft_strdup(ft_strchr(str, '\0'));
		free(temp);
		return (str);
	}
	return (str);
}

char	*check_str(char *str, char **line)
{
	char *temp;

	temp = str;
	if (str[0] == '\n' && str[1] == '\0')
	{
		str = ft_strdup(ft_strchr(str, '\n') + 1);
		free(temp);
	}
	else if (str[0] == '\n' && str[1] != '\0' &&
			ft_strchr(str + 1, '\n'))
	{
		str = ft_strdup(ft_strchr(str, '\n') + 1);
		free(temp);
		str = create_last_str(str, line);
	}
	else if (str[0] == '\n' && str[1] != '\0' &&
			ft_strchr(str + 1, '\n') == NULL)
	{
		str = ft_strdup(ft_strchr(str, '\n') + 1);
		free(temp);
	}
	return (str);
}

int		ft_free(char **str)
{
	char *temp;

	temp = *str;
	free(temp);
	*str = NULL;
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*str;
	char		buf[10 + 1];
	int			ret;
	char		*temp;

	if (((!str && !(str = ft_strnew(0)))) ||
			(fd < 0 || !line || read(fd, buf, 0) < 0))
		return (-1);
	str = check_str(str, line);
	if (ft_strchr(str, '\n') == NULL)
	{
		while (!(ft_strchr(str, '\n')) && (ret = read(fd, buf, 10)))
		{
			buf[ret] = '\0';
			temp = str;
			str = ft_strjoin(str, buf);
			free(temp);
			g_read = 1;
		}
		str = create_last_str(str, line);
	}
	if (ft_strlen(str) == 0 && !ret)
		return (ft_free(&str));
	return (1);
}
