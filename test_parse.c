/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:35:21 by minkyu            #+#    #+#             */
/*   Updated: 2023/01/29 11:08:20 by minkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"
#include "../includes/process.h"
#include <stdlib.h>

extern char **environ;
void	add_newnode(t_cmd **head, char **input, int pipe_cnt, int *exit_stat);
void	print_node(t_cmd *head);

t_env *g_env;

t_cmd *test_parse(void)
{
	t_cmd	*head = NULL;
	int		*exit_stat = malloc(sizeof(int));
	
	set_envlist(environ);

	int		pipe_cnt = 0;
	add_newnode(&head, ft_split("sleep 100", ' '), pipe_cnt, exit_stat);
	// add_newnode(&head, ft_split("<< EOF", ' '), pipe_cnt, exit_stat);
	// add_newnode(&head, ft_split("|", ' '), pipe_cnt, exit_stat);
	// add_newnode(&head, ft_split("cat -e", ' '), pipe_cnt, exit_stat);
	
	//print_node(head);
	//system("leaks minishell");
	return (head);
}

void	print_node(t_cmd *head)
{
	int i = 0;
	char **input;
	
	while (head)
	{
		i = 0;
		input = head->input;
		printf("input : \n");
		while (input[i])
		{
			printf("%s\n", input[i]);
			i++;
		}
		printf("type : %d\n", head->type);
		printf("pipe_cnt : %d\n", head->pipe_cnt);
		printf("unit_cnt : %d\n", head->unit_cnt);
		printf("=========================================\n");
		head = head->next;
	}
}

void	add_newnode(t_cmd **head, char **input, int pipe_cnt, int *exit_stat)
{
	static int	unit_cnt;
	t_cmd		*new;
	t_cmd		*tmp;

	new = malloc(sizeof(t_cmd));
	new->input = input;
	new->pipe_cnt = pipe_cnt;
	if (**input == '|')
	{
		new->type = pipeline;
		unit_cnt++;
	}
	else if (**input == '<' || **input == '>')
		new->type = redirect;
	else
		new->type = word;
	new->unit_cnt = unit_cnt;
	new->exit_stat = exit_stat;
	new->next = NULL;
	tmp = (*head);
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		(*head) = new;
}