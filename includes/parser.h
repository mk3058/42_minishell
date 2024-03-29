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

// default
# define NONE			0

// is_in_quote function
# define DQUOTE 		1
# define SQUOTE			2

// is_cmd function
# define PIPE			1
# define REDIR			2
# define DOUBLED_REDIR	3

# include "../includes/minishell.h"

typedef struct s_cmd	t_cmd;

//space_token.c
char	**get_space_token(char *line);
int		tokenize_space(char **token, char *line, int *idx, int *start);
int		cnt_space(char *line);

//cmd_token.c
char	**get_cmd_token(char **line);
int		tokenize_cmd(char **token, char *line, int i, int *idx);
int		cnt_cmd(char **line);
void	check_cmd_cnt(char *line, int *i, int *cnt);

//parser.c
t_cmd	*get_unit_token(char *line);
t_cmd	*get_cmd_info(char **token);
void	init_type(t_cmd *cmd);
void	init_input(t_cmd *cmd, char **token, int unit);
t_cmd	*init_input_util(t_cmd *cmd, char **token, int *i, int *unit);

//parse_util.c
void	free_2d_arr(char **arr);
int		is_in_quote(char *line, int idx);
int		is_cmd(char *line, int idx);
char	*no_quote_strdup(char *s1);
char	**ft_2d_strndup(char **arr, int len);

//parse_err.c
int		check_error(char **token);
int		print_err(char *str);

//init_cmd.c
t_cmd	*cmd_lstinit(void);
void	cmd_lstadd(t_cmd *head);
void	remove_quotes(char **input);
int		cnt_pipe(char **token);

//parse_path.c
char	**check_path(char	**token);
char	*join_path(char *str, int i);
char	**cp_create_arr(char **arr);

#endif