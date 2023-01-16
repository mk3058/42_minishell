# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bojung <bojung@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 11:50:47 by bojung            #+#    #+#              #
#    Updated: 2022/07/14 19:26:15 by bojung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -c -Wall -Wextra -Werror

NAME = libft.a
SOURCES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c				\
		  ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c		\
		  ft_strlcat.c ft_strncmp.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c	\
		  ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c		\
		  ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c		\
		  ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c	\
		  ft_printf.c ft_specifier.c ft_dllist.c ft_dllist2.c get_next_line.c
		  
SOURCES_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJS_MAN = $(SOURCES:.c=.o)
OBJS_BONUS = $(SOURCES_BONUS:.c=.o)

ifdef ISBONUS
	OBJS = $(OBJS_MAN) $(OBJS_BONUS)
else
	OBJS = $(OBJS_MAN)
endif

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	@ar cr $@ $^

clean:
	@rm -f $(OBJS_MAN) $(OBJS_BONUS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus :
	make ISBONUS=1 all

.PHONY : all clean fclean re bonus
