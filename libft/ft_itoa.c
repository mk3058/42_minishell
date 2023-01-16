/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <bojung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:28:23 by bojung            #+#    #+#             */
/*   Updated: 2022/07/14 15:25:06 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_getlen(int n);

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	int			sign;
	long long	tmp;

	len = my_getlen(n);
	tmp = (long long)n;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	sign = 1;
	if (tmp < 0)
	{
		sign = -1;
		tmp = -tmp;
	}
	str[len] = '\0';
	while (len--)
	{
		str[len] = tmp % 10 + '0';
		tmp /= 10;
	}
	if (sign < 0)
		str[0] = '-';
	return (str);
}

static int	my_getlen(int n)
{
	int	len;

	if (n == 0)
		return (1);
	if (n < 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}
