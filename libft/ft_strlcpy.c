/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <bojung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:05:42 by bojung            #+#    #+#             */
/*   Updated: 2022/07/12 13:31:43 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;
	char	*src_cpy;

	src_cpy = (char *)src;
	i = 0;
	len = 0;
	while (src_cpy[len] != '\0')
		len++;
	i = 0;
	if (dstsize > 0)
	{
		while (src_cpy[i] != '\0' && i < dstsize - 1)
		{
			dst[i] = src_cpy[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}
