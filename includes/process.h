/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:30:14 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/18 17:53:19 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <fcntl.h>
# include <unistd.h>

# include "../includes/minishell.h"
# include "../includes/malloc_ctl.h"

//here_doc.c
void	heredoc(t_cmd *cmd);

//redirect.c
int		*get_redirect_fd(t_cmd *cmd, int unit_cnt);

//set_fd.c
int		**make_pipe(t_cmd *cmd);
int		set_fd(int **fd, int proc_cnt, int child_num);
void	close_fd(int **fd, int proc_cnt, int child_num);

//util.c
int		is_equal(char *str1, char *str2);
void	exit_err(char *err_message, char *prefix, char *postfix);

//command.c
void	execute_cmd(t_cmd *cmd, char **envp, int child_num, int **fd);

#endif