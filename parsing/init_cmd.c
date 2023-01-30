/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bojung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:28:02 by bojung            #+#    #+#             */
/*   Updated: 2023/01/26 13:28:03 by bojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_cmd	*cmd_lstinit(void)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new == 0)
		return (0);
	new->input = NULL;
	new->type = 0;
	new->pipe_cnt = 0;
	new->unit_cnt = 0;
	new->exit_stat = 0;
	new->next = NULL;
	return (new);
}

void	cmd_lstadd(t_cmd *head)
{
	t_cmd	*node;

	node = cmd_lstinit();
	head->next = node;
	node->next = NULL;
}

void	cmd_clear(t_cmd *head)
{
	t_cmd	*tmp;

	if (!head)
	{
		printf("free_all Err: head node is null!\n");
		return ;
	}
	tmp = head;
	//전부 free 해줘야 함.
	while (tmp)
	{
		head = tmp;
		free_2d_arr(tmp->input);
		tmp = tmp->next;
		free(head);
	}
}
