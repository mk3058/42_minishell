#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h> //open close
# include <termios.h>

# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define DFL 0
# define IGN 1
# define HAN 2

char	*get_next_line(int fd);
void	set_signal(int sigint, int sigquit);
void	signal_handler(int sig);

enum	e_str_type {word, pipeline, redirect};

typedef struct s_cmd
{
	char			**input;
	int				type;
	int				pipe_cnt;
	int				unit_cnt;
	int				*exit_stat;
	struct s_cmd	*next;
}	t_cmd;

#endif