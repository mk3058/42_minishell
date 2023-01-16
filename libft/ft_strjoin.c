/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <bojung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:57:00 by bojung            #+#    #+#             */
/*   Updated: 2022/07/11 13:01:36 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		idx_s1;
	int		idx_s2;

	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == 0)
		return (0);
	idx_s1 = 0;
	idx_s2 = 0;
	while (s1[idx_s1] != '\0')
	{
		str[idx_s1] = (char)s1[idx_s1];
		idx_s1++;
	}
	while (s2[idx_s2] != '\0')
	{
		str[idx_s1 + idx_s2] = (char)s2[idx_s2];
		idx_s2++;
	}
	str[idx_s1 + idx_s2] = '\0';
	return (str);
}
