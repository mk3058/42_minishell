/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:30:14 by minkyuki          #+#    #+#             */
/*   Updated: 2023/02/01 12:57:42 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <fcntl.h>
# include <unistd.h>

# include "../includes/minishell.h"
# include "../includes/environment.h"
# include "../includes/builtin.h"
# include "../includes/util.h"

//here_doc.c
int		heredoc(t_cmd *cmd);

//redirect.c
int		*get_redirect_fd(t_cmd *cmd, int unit_cnt);

//set_fd.c
int		**make_pipe(t_cmd *cmd);
int		set_redirect(t_cmd *cmd, int **fd, int child_num);
int		*set_fd(int **fd, int proc_cnt, int child_num);
void	close_fd(int **fd, int proc_cnt, int child_num);

//command.c
void	execute_cmd(t_cmd *cmd, int child_num, int **fd);
char	*find_path(t_cmd *cmd);

//process.c
void	process(t_cmd *cmd);

#endif