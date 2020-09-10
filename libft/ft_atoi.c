/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:48:50 by dmontgen          #+#    #+#             */
/*   Updated: 2019/11/15 15:43:23 by dmontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *nptr)
{
	long	resultat;
	int		signe;

	resultat = 0;
	signe = 1;
	while (*nptr == 32 || (*nptr > 8 && *nptr < 14))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signe = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		resultat *= 10;
		resultat += (long)*nptr - 48;
		nptr++;
	}
	if (resultat < 0)
		resultat = (signe < 0) ? 0 : -1;
	return (int)(resultat * signe);
}
