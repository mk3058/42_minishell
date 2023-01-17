/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:30:14 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/17 16:25:44 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <fcntl.h>
# include <unistd.h>

# include "../includes/minishell.h"
# include "../includes/malloc_ctl.h"

int		is_equal(char *str1, char *str2);
int		cnt_pipe(t_cmd *cmd);
int		**make_pipe(t_cmd *cmd);
int		*get_redirect_fd(t_cmd *cmd, int unit_cnt);
void	heredoc(t_cmd *cmd);

#endif