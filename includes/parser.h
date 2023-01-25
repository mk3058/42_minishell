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

// is_in_quote function
# define NONE			0
# define DQUOTE 		1
# define SQUOTE			2

// is_cmd function
# define PIPE			1
# define REDIR			2
# define DOUBLED_REDIR	3

# include "../includes/minishell.h"

typedef struct s_plist
{
	char	*str;
	//int		quote_flag;
}	t_plist;

//get_token.c
char	**get_space_token(char *line);
int		cnt_space(char *line);
char	**get_cmd_token(char **line);
int		cnt_cmd(char **line);

//parser.c
char	**get_unit_token(char *line);

//parse_util.c
int		is_in_quote(char *line, int idx);
int		is_cmd(char *line, int idx);
char	*get_substr(char const *s, unsigned int start, size_t len);
int		check_error(char **token);

#endif