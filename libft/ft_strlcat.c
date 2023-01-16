/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <bojung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:07:19 by bojung            #+#    #+#             */
/*   Updated: 2022/07/13 12:08:39 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_add;
	size_t	dst_length;
	size_t	src_length;

	dst_length = ft_strlen(dst);
	src_length = ft_strlen(src);
	len_add = 0;
	if (dst_length >= dstsize)
		return (src_length + dstsize);
	while (src[len_add] != '\0' && dst_length + len_add + 1 < dstsize)
	{
		dst[dst_length + len_add] = src[len_add];
		len_add++;
	}
	dst[dst_length + len_add] = '\0';
	return (dst_length + src_length);
}
