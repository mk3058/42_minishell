#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h> //open close

# include "../libft/libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

char	*get_next_line(int fd);


#endif

