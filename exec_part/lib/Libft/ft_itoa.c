/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalmi <asalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:27:18 by asalmi            #+#    #+#             */
/*   Updated: 2024/09/18 20:01:50 by asalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length_n(long long n)
{
	int	len;

	len = 0;
	if (n < 1)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static long long	absolute_value(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*str;
	int				sign;
	unsigned int	nbr;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = length_n(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (str);
	str[len] = '\0';
	nbr = absolute_value(n);
	while (len--)
	{
		str[len] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
