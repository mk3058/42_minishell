/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:30:14 by minkyuki          #+#    #+#             */
/*   Updated: 2023/02/01 15:20:00 by minkyuki         ###   ########.fr       */
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
void	heredoc(t_cmd *cmd);

//redirect.c
int		*get_redirect_fd(t_cmd *cmd, int unit_cnt);

//set_fd.c
int		**make_pipe(t_cmd *cmd);
int		*set_fd(int **fd, int proc_cnt, int child_num);
void	close_fd(int **fd, int proc_cnt, int child_num);

//command.c
void	execute_cmd(t_cmd *cmd, int child_num, int **fd);
char	*find_path(t_cmd *cmd);

//process.c
void	process(t_cmd *cmd);

#endif