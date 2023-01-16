/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <bojung@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:33:17 by bojung            #+#    #+#             */
/*   Updated: 2022/07/12 13:25:30 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define TRUE	1
# define FALSE	0
# define BUFFER_SIZE 10

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_dllnode
{
	int					data;
	struct s_dllnode	*prev;
	struct s_dllnode	*next;
}	t_dllnode;

typedef struct s_DoubleLinkedList
{
	t_dllnode	*head;
	t_dllnode	*tail;
	int			size;
}	t_DoubleLinkedList;

typedef t_DoubleLinkedList	t_dll;

int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *s, int c);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_isprint(int c);
int			ft_isdigit(int c);
int			ft_isascii(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
int			ft_atoi(const char *str);

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

int			ft_printf(const char *format, ...);
void		format_print(char sp, va_list ap, int *ret);
int			ft_printchar(char c);
int			ft_printstr(char *str);
int			ft_putnbr_hex_p(unsigned long long nbr, char conv);
int			ft_putnbr_hex(unsigned int nbr, char conv);
int			ft_putnbr_int(long long nbr);

t_dll		*dll_init(void);
int			dll_isempty(t_dll *pdll);
void		dll_add_first(t_dll *pdll, int data);
void		dll_add_last(t_dll *pdll, int data);
int			dll_remove_first(t_dll *pdll);
int			dll_remove_last(t_dll *pdll);
void		dll_clear(t_dll *pdll);
void		dll_print(t_dll *pdll1, t_dll *pdll2);
void		dll_swap(t_dll *pdll, t_dllnode *node);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

char		*get_next_line(int fd);

#endif
