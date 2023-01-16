/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <bojung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:30:03 by bojung            #+#    #+#             */
/*   Updated: 2022/07/13 12:43:42 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	cnt_words(char *s, char c);
static char		**for_free(char **arr);
static char		*ft_strndup(const char *s1, size_t n);

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	save;
	size_t	index;

	i = 0;
	index = 0;
	if (!s)
		return (0);
	arr = (char **)malloc(sizeof(char *) * (cnt_words((char *)s, c) + 1));
	if (arr == 0)
		return (0);
	while (index < cnt_words((char *)s, c))
	{
		while (s[i] == c)
			i++;
		save = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		arr[index] = ft_strndup((const char *)(s + save), i - save);
		if (arr[index++] == NULL)
			return (for_free(arr));
	}
	arr[index] = 0;
	return (arr);
}

static char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	if (n == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == 0)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**for_free(char **arr)
{
	size_t	idx;

	idx = 0;
	while (arr[idx])
	{
		free(arr[idx]);
		idx++;
	}
	free(arr);
	return (NULL);
}

static size_t	cnt_words(char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!*s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i + 1] == c && s[i + 1] != '\0')
			len++;
		i++;
	}
	if (s[i - 1] == c)
		len--;
	return (len + 1);
}
