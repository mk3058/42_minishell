/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <bojung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:58:53 by bojung            #+#    #+#             */
/*   Updated: 2022/07/11 16:03:05 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	tmp;
	char		c;

	if (fd < 0)
		return ;
	tmp = (long long)n;
	if (n < 0)
	{
		tmp = -tmp;
		write(fd, "-", 1);
	}
	if (tmp >= 10)
	{
		c = tmp % 10 + '0';
		ft_putnbr_fd(tmp / 10, fd);
	}
	else
		c = tmp + '0';
	write(fd, &c, 1);
}
