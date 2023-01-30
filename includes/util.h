/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:35:39 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/30 17:49:33 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include <stdio.h>
# include <sys/errno.h>
# include <unistd.h>

# include "../libft/libft.h"

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}	t_garbage;

t_garbage	*get_new_list(void	*ptr);
void		add_ptr(void *ptr, t_garbage *head);
void		free_all(t_garbage *head);

int			\
err_print(char *prefix, char *errmsg, char *postfix, int return_val);
int			is_equal(char *str1, char *str2);

#endif