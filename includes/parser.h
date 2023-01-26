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

typedef struct s_cmd t_cmd;

//get_token.c
char	**get_space_token(char *line);
int		cnt_space(char *line);
char	**get_cmd_token(char **line);
int		cnt_cmd(char **line);

//parser.c
char	**get_unit_token(char *line);
t_cmd	*get_cmd_info(char **token);
void	init_type(t_cmd *cmd);
void	init_input(t_cmd *cmd, char **token);
void	init_pipe_cnt(t_cmd cmd, char **token);


//parse_util.c
void	free_2d_arr(char **arr);
int		is_in_quote(char *line, int idx);
int		is_cmd(char *line, int idx);
char	*get_saubstr(char const *s, unsigned int start, size_t len);
char	**ft_2d_strndup(char **arr, int	len);
int		cnt_pipe(char **token);

//parse_err.c
int		check_error(char **token);
int		err_special_char(char *token);
int		print_err(char *str);

//init_cnd.c
t_cmd	*cmd_lstinit(void);
void	cmd_lstadd(t_cmd *head);

#endif