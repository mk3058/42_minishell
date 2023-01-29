# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 16:17:34 by bojung            #+#    #+#              #
#    Updated: 2023/01/29 10:51:26 by minkyu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CCFLAGS		= -Wall -Wextra -Werror
RLFLAG		= -lreadline -L/opt/homebrew/opt/readline/lib
COMPILEFLAG	= -I/opt/homebrew/opt/readline/include
NAME		= minishell

RM			= rm -rf
AR			= ar crs
LIBFTDIR	= ./libft
LIBNAME		= libft.a

HEADDIR		= ./includes

SRCDIR		= ./srcs
SRCFILES	= get_next_line.c
UTILDIR		= ./util
UTILFILES	= malloc_ctl.c util.c
PROCESSDIR	= ./process
PROCESSFILES= command.c here_doc.c process.c redirect.c set_fd.c
ENVDIR		= ./environment
ENVFILES	= env_util.c env.c
BUILTINDIR	= ./builtin_func
BUILTINFILES= cd.c controller.c echo.c env.c exit.c export.c pwd.c unset.c

SRCS	= $(addprefix $(SRCDIR)/, $(SRCFILES)) $(addprefix $(UTILDIR)/, $(UTILFILES))\
$(addprefix $(PROCESSDIR)/, $(PROCESSFILES)) $(addprefix $(ENVDIR)/, $(ENVFILES)) $(addprefix $(BUILTINDIR)/, $(BUILTINFILES))
OBJS	= $(SRCS:.c=.o)

SRCS_MAIN		= main.c signal.c test_parse.c
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

bonus: $(NAME) $(NAME2)

.PHONY : all clean fclean re
