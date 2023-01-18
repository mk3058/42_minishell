/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_ctl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:35:20 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/17 14:51:07 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc_ctl.h"

void	free_all(t_garbage *head)
{
	t_garbage	*tmp;

	if (!head)
	{
		printf("free_all Err: head node is null!\n");
		return ;
	}
	tmp = head;
	while (tmp)
	{
		free(tmp->ptr);
		tmp = tmp->next;
	}
	free(head);
}

void	add_ptr(void *ptr, t_garbage *head)
{
	t_garbage	*tmp;

	if (!head)
	{
		printf("add_ptr Err: head node is null!\n");
		return ;
	}
	tmp = malloc(sizeof(t_garbage));
	tmp->ptr = ptr;
	tmp->next = head;
	head = tmp;
}

t_garbage	*get_new_list(void	*ptr)
{
	t_garbage	*head;

	head = malloc(sizeof(t_garbage));
	head->ptr = ptr;
	head->next = NULL;
	return (head);
}
