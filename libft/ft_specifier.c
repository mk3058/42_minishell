/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <bojung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:20:22 by bojung            #+#    #+#             */
/*   Updated: 2022/07/28 15:29:47 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (ft_strlen("(null)"));
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_putnbr_int(long long nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
		len++;
	}
	if (nbr / 10 != 0)
		len = len + ft_putnbr_int(nbr / 10);
	write(1, &"0123456789"[nbr % 10], 1);
	return (len + 1);
}

int	ft_putnbr_hex_p(unsigned long long nbr, char sp)
{
	int		len;

	len = 0;
	if (sp == 'p')
	{
		ft_putstr_fd("0x", 1);
		len += 2;
		sp = 0;
	}
	if (nbr / 16 != 0)
		len = len + ft_putnbr_hex_p(nbr / 16, sp);
	write(1, &"0123456789abcdef"[nbr % 16], 1);
	return (len + 1);
}

int	ft_putnbr_hex(unsigned int nbr, char sp)
{
	int		len;

	len = 0;
	if (nbr / 16 != 0)
		len = len + ft_putnbr_hex(nbr / 16, sp);
	if (sp == 'X')
		write(1, &"0123456789ABCDEF"[nbr % 16], 1);
	else
		write(1, &"0123456789abcdef"[nbr % 16], 1);
	return (len + 1);
}
