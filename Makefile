CC			= cc
CCFLAGS		= -Wall -Wextra -Werror
RLFLAG		= -lreadline -L${HOME}/.brew/opt/readline/lib
COMPILEFLAG	= -I${HOME}/.brew/opt/readline/include
NAME		= minishell

RM			= rm -rf
AR			= ar crs
LIBFTDIR	= ./libft
LIBNAME		= libft.a

HEADDIR		= ./includes

SRCDIR		= ./srcs
SRCFILES	= signal.c get_next_line.c

PROC_SRCDIR		= ./process
PROC_SRCFILES	= command.c here_doc.c process.c redirect.c set_fd.c

ENVP_SRCDIR		= ./environment
ENVP_SRCFILES	= env_util.c env.c

UTIL_DIR		= ./util
UTIL_FILES	= malloc_ctl.c util.c

PARSE_SRCDIR	= ./parsing
PARSE_SRCFILES	= parser.c parse_util.c space_token.c cmd_token.c parse_err.c init_cmd.c

BUILTIN_DIR	= ./builtin_func
BUILTIN_FILES= cd.c controller.c echo.c env.c exit.c export.c pwd.c unset.c

SRCS	= $(addprefix $(SRCDIR)/, $(SRCFILES)) \
			$(addprefix $(PARSE_SRCDIR)/, $(PARSE_SRCFILES))\
			$(addprefix $(ENVP_SRCDIR)/, $(ENVP_SRCFILES))\
			$(addprefix $(PROC_SRCDIR)/, $(PROC_SRCFILES))\
			$(addprefix $(UTIL_DIR)/, $(UTIL_FILES))\
			$(addprefix $(BUILTIN_DIR)/, $(BUILTIN_FILES))
OBJS	= $(SRCS:.c=.o)

SRCS_MAIN		= main.c
OBJS_MAIN		= $(SRCS_MAIN:.c=.o)

%.o: %.c
	$(CC) -c $(CCFLAGS) -I$(HEADDIR) $(COMPILEFLAG) $< -o $@

$(NAME): $(OBJS_MAIN) $(OBJS)
	$(MAKE) all -C $(LIBFTDIR)
	$(CC) $(CCFLAGS) -L $(LIBFTDIR) -lft $^ -o $@ $(RLFLAG)

all: $(NAME)

clean:
	$(RM) $(OBJS_MAIN)
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean:
	$(RM) $(OBJS_MAIN)
	$(RM) $(OBJS)
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY : all clean fclean re
