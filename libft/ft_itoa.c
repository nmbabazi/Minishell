/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:41:21 by dmontgen          #+#    #+#             */
/*   Updated: 2019/11/06 16:54:06 by dmontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_len_nb(int n, int temp)
{
	int len;

	len = 0;
	if (n == 0)
	{
		len = 1;
		return (len);
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	if (temp < 0)
		len++;
	return (len);
}

char	*ft_putstring(int n, int len, char *str)
{
	len--;
	while (len >= 0 && n > 0)
	{
		if (n >= 10)
		{
			str[len] = (n % 10) + 48;
			n = n / 10;
		}
		else
		{
			str[len] = n + 48;
			n = n / 10;
		}
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*newstr;
	int		temp;
	int		len;

	newstr = NULL;
	temp = n;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		n *= -1;
	len = ft_len_nb(n, temp);
	if (!(newstr = ft_strnew(len)))
		return (NULL);
	if (n == 0)
		newstr[0] = 48;
	ft_putstring(n, len, newstr);
	if (temp < 0)
		newstr[0] = '-';
	return (newstr);
}
