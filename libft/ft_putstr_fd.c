/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <bojung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:35:25 by bojung            #+#    #+#             */
/*   Updated: 2022/07/11 16:01:20 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	len;
	size_t	idx;

	if (!s || fd < 0)
		return ;
	idx = 0;
	len = ft_strlen(s);
	while (idx < len)
	{
		write(fd, &s[idx], 1);
		idx++;
	}
}
