#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"
char	*copy_str(char *str, int chunk_len);
int		cnt_chunk(char *str, char **charset);
int		find_chunk_len(char *str, char **charset);

char	**my_split(char *str, char *charset[])
{
	char	**result;
	int		chunk_len;
	int		result_ind;

	result_ind = -1;
	result = malloc(sizeof(char *) * (cnt_chunk(str, charset) + 1));
	while (*str)
	{
		chunk_len = find_chunk_len(str, charset);
		if (chunk_len > 0)
		{
			result[++result_ind] = copy_str(str, chunk_len);
			if (!result[result_ind])
				return (0);
		}
		str += (chunk_len);
	}
	result[++result_ind] = 0;
	return (result);
}

char	*copy_str(char *str, int chunk_len)
{
	char	*copy;
	int		i;

	i = -1;
	copy = malloc(sizeof(char) * chunk_len + 1);
	if (!copy)
		return (0);
	while (++i < chunk_len)
		copy[i] = str[i];
	copy[i] = '\0';
	return (copy);
}

int	cnt_chunk(char *str, char **charset)
{
	int	i = -1;
	int	j = -1;
	int	cnt = 0;

	while (str[++i])
	{
		j = -1;
		while (charset[++j])
		{
			if (ft_strncmp(&str[i], charset[j], ft_strlen(charset[j])) == 0)
			{
				cnt++;
				i += (ft_strlen(charset[j]) - 1);
				break;
			}
		}
	}
	return (2 * cnt + 1);
}

int	find_chunk_len(char *str, char **charset)
{
	int i = -1;
	int	j = -1;

	while (charset[++j])
	{
		if (ft_strncmp(&str[0], charset[j], ft_strlen(charset[j])) == 0)
			return (ft_strlen(charset[j]));
	}
	while (str[++i])
	{
		j = -1;
		while (charset[++j])
		{
			if (ft_strncmp(&str[i], charset[j], ft_strlen(charset[j])) == 0)
				return (i);
		}
	}
	return (i);
}
