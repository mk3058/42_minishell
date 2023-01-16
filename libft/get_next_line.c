/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <bojung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 16:28:08 by bojung            #+#    #+#             */
/*   Updated: 2022/08/17 16:03:34 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strchr_gnl(const char *s, int c)
{
	int	index;

	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == (char)c)
			return (index);
		index++;
	}
	return (-1);
}

static char	*find_nl(int fd, char *buf, char *backup)
{
	int		size;
	char	*temp;

	size = 1;
	while (size > 0)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1)
			return (NULL);
		if (size == 0)
			break ;
		buf[size] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		backup = ft_strjoin(temp, buf);
		if (!backup)
			return (NULL);
		free(temp);
		temp = NULL;
		if (ft_strchr_gnl(buf, '\n') >= 0)
			break ;
	}
	return (backup);
}

static char	*get_rl(char *line)
{
	int		sep;
	char	*rest_line;

	sep = ft_strchr_gnl(line, '\n');
	if (sep >= 0)
	{
		rest_line = ft_strdup(line + sep + 1);
		if (!rest_line)
			return (NULL);
		if (!*rest_line)
		{
			free(rest_line);
			rest_line = NULL;
			return (NULL);
		}
		line[sep + 1] = '\0';
		return (rest_line);
	}
	else
		return (0);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		buf[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = find_nl(fd, buf, backup);
	if (!line)
		return (NULL);
	backup = get_rl(line);
	return (line);
}
