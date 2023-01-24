# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 16:17:34 by bojung            #+#    #+#              #
#    Updated: 2023/01/16 15:44:37 by minkyuki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
SRCFILES	= signal.c parser.c parser_util.c

SRCDIR		= ./environment
SRCFILES	= env.c print_list.c

SRCS	= $(addprefix $(SRCDIR)/, $(SRCFILES)) $(addprefix $(ENVSRCDIR)/, $(ENVSRCFILES))
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
