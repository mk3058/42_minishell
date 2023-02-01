/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:24:56 by minkyu            #+#    #+#             */
/*   Updated: 2023/02/01 11:55:16 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <termios.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

# include "../libft/libft.h"
# include "../includes/parser.h"
# include "../includes/environment.h"
# include "../includes/signal.h"

char	*get_next_line(int fd);

enum	e_str_type {word, pipeline, redirect};

typedef struct s_cmd
{
	char			**input;
	int				type;
	int				pipe_cnt;
	int				unit_cnt;
	struct s_cmd	*next;
}	t_cmd;

#endif