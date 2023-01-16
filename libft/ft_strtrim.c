/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <bojung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:24:01 by bojung            #+#    #+#             */
/*   Updated: 2022/07/11 19:54:58 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		idx_fst;
	int		idx_lst;

	if (!s1 || !set)
		return (0);
	idx_fst = 0;
	idx_lst = ft_strlen(s1);
	while (s1[idx_fst] && ft_strchr(set, s1[idx_fst]))
		idx_fst++;
	while (idx_lst - 1 >= 0 && ft_strchr(set, s1[idx_lst - 1]))
		idx_lst--;
	if (idx_lst - idx_fst < 0)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (idx_lst - idx_fst + 1));
	if (str == 0)
		return (0);
	ft_strlcpy(str, s1 + idx_fst, idx_lst - idx_fst + 1);
	return (str);
}
