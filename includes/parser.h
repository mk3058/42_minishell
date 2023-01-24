/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 10:59:52 by bojung            #+#    #+#             */
/*   Updated: 2023/01/24 10:59:53 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define NONE	0
# define DQUOTE 1
# define SQUOTE 2

# include "../includes/minishell.h"

typedef struct s_prs
{
	int	quote_flag;
}	t_prs;

char	**get_space_token(char *line);
int		cnt_space(char *line);
int		cnt_cmd(char **line);

char	**get_unit_token(char *line);

int		is_in_quote(char *line, int idx);
char	*get_substr(char const *s, unsigned int start, size_t len);


#endif