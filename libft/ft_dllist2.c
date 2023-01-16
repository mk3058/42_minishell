/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dllist2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:56:02 by bojung            #+#    #+#             */
/*   Updated: 2022/10/24 16:56:04 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	dll_add_first(t_dll *pdll, int data)
{
	t_dllnode	*new;

	new = (t_dllnode *)malloc(sizeof(t_dllnode));
	new->data = data;
	if (dll_isempty(pdll))
	{
		pdll->tail = new;
		new->next = new;
		new->prev = new;
	}
	else
	{
		pdll->tail->next = new;
		pdll->head->prev = new;
		new->prev = pdll->tail;
		new->next = pdll->head;
	}
	pdll->head = new;
	(pdll->size)++;
}

void	dll_add_last(t_dll *pdll, int data)
{
	t_dllnode	*new;

	new = (t_dllnode *)malloc(sizeof(t_dllnode));
	new->data = data;
	if (dll_isempty(pdll))
	{
		pdll->head = new;
		new->prev = new;
		new->next = new;
	}
	else
	{
		pdll->head->prev = new;
		pdll->tail->next = new;
		new->prev = pdll->tail;
		new->next = pdll->head;
	}
	pdll->tail = new;
	(pdll->size)++;
}

int	dll_remove_first(t_dll *pdll)
{
	t_dllnode	*rnode;
	int			rdata;

	rnode = pdll->head;
	rdata = pdll->head->data;
	if (pdll->head == pdll->tail)
		pdll->head = NULL;
	else
	{
		pdll->head = pdll->head->next;
		pdll->tail->next = pdll->head;
	}
	if (pdll->head == NULL)
		pdll->tail = NULL;
	else
		pdll->head->prev = pdll->tail;
	(pdll->size)--;
	free(rnode);
	return (rdata);
}

int	dll_remove_last(t_dll *pdll)
{
	t_dllnode	*rnode;
	int			rdata;

	rnode = pdll->tail;
	rdata = pdll->tail->data;
	if (pdll->head == pdll->tail)
		pdll->tail = NULL;
	else
	{
		pdll->tail = pdll->tail->prev;
		pdll->head->prev = pdll->tail;
	}
	free(rnode);
	if (pdll->tail == NULL)
		pdll->head = NULL;
	else
		pdll->tail->next = pdll->head;
	(pdll->size)--;
	return (rdata);
}

void	dll_swap(t_dll *pdll, t_dllnode *node)
{
	t_dllnode	*temp;

	if (pdll->size != 1)
	{
		temp = node->next->next;
		if (node == pdll->head)
			pdll->head = node->next;
		if (node->next == pdll->tail)
			pdll->tail = node;
		node->prev->next = node->next;
		node->next->next->prev = node;
		node->next->next = node;
		node->next->prev = node->prev;
		node->prev = node->next;
		node->next = temp;
	}
}
