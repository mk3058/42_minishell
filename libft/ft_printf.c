/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:00:14 by bojung            #+#    #+#             */
/*   Updated: 2023/01/29 10:54:56 by minkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_len(long long nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		len++;
	}
	if (nbr / 10 != 0)
		len = len + digit_len(nbr / 10);
	return (len + 1);
}

static int	print_space(const char *format, va_list ap)
{
	va_list	ap_cpy;
	int		size;
	char	*space_num;
	int		i;
	int		arg;

	i = 0;
	size = 0;
	while (*(format + size) >= '0' && *(format + size) <= '9')
		size++;
	if (size == 0)
		return (0);
	space_num = (char *)malloc(sizeof(char) * size + 1);
	ft_strlcpy(space_num, format, size + 1);
	va_copy(ap_cpy, ap);
	arg = digit_len(va_arg(ap_cpy, int));
	while (i++ < ft_atoi(space_num) - arg)
		write(1, " ", 1);
	free(space_num);
	va_end(ap_cpy);
	return (size);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	ret = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 0)
				break ;
			format += print_space(format, ap);
			format_print(*format, ap, &ret);
		}
		else
		{
			ft_putchar_fd(*format, 1);
			ret++;
		}
		format++;
	}
	va_end(ap);
	return (ret);
}

void	format_print(char sp, va_list ap, int *ret)
{
	if (sp == 'c')
		*ret = *ret + ft_printchar(va_arg(ap, int));
	else if (sp == 's')
		*ret = *ret + ft_printstr(va_arg(ap, char *));
	else if (sp == 'p')
		*ret = *ret + ft_putnbr_hex_p(va_arg(ap, unsigned long long), sp);
	else if (sp == 'd' || sp == 'i')
		*ret = *ret + ft_putnbr_int(va_arg(ap, int));
	else if (sp == 'u')
		*ret = *ret + ft_putnbr_int(va_arg(ap, unsigned int));
	else if (sp == 'x' || sp == 'X')
		*ret = *ret + ft_putnbr_hex(va_arg(ap, unsigned int), sp);
	else if (sp == '%')
	{
		ft_putchar_fd('%', 1);
		(*ret)++;
	}
}
