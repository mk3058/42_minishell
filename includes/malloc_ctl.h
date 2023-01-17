/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_ctl.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:35:39 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/17 14:51:31 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_CTL_H
# define MALLOC_CTL_H

# include <stdio.h>

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}	t_garbage;

t_garbage	*get_new_list(void	*ptr);
void		add_ptr(void *ptr, t_garbage *head);
void		free_all(t_garbage *head);

#endif