/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:49:25 by bojung            #+#    #+#             */
/*   Updated: 2023/01/24 13:49:25 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void free_all(char *cmd_path, char **token)
{
	int	i;

	i = 0;
	while(token[i])
	{
		free(token[i]);
		i++;
	}
	free(token);
	free(cmd_path);
}

char	*parsing_word(char *line)
{
	struct stat	stat_buf;
	char		**token;
	char		*tmp;
	char		*cmd_path;
	int			i;

	i = -1;
	token = ft_split(getenv("PATH"), ':');
	while (token[++i])
	{
		tmp = ft_strjoin(token[i], "/");
		cmd_path = ft_strjoin(tmp, line);
		free(tmp);
		if (!stat(cmd_path, &stat_buf))
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	free_all(cmd_path, token);
	return (cmd_path);
}
