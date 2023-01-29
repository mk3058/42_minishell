/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:35:21 by minkyu            #+#    #+#             */
/*   Updated: 2023/01/29 15:09:23 by minkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"
#include "../includes/process.h"
#include <stdlib.h>

extern char **environ;
void	add_newnode(t_cmd **head, char **input, int pipe_cnt, int *exit_stat);
void	print_node(t_cmd *head);
char	**my_split(char *str, char **charset);
char 	**pre_split(char *line);

t_env *g_env;

t_cmd *test_parse(char *line)
{
	t_cmd	*head = NULL;
	int		*exit_stat = malloc(sizeof(int));
	char	**tokenize = pre_split(line);
	int		i = 0;
	int		pipe_cnt = 0;
	set_envlist(environ);

	while (line[i])
		if (line[i++] == '|')
			pipe_cnt++;
	i = 0;
	while (tokenize[i])
	{
		add_newnode(&head, ft_split(tokenize[i], ' '), pipe_cnt, exit_stat);
		i++;
	}
	
	print_node(head);
	//system("leaks minishell");
	return (head);
}

char **pre_split(char *line)
{
	char *charset[] = {"|", "<<", ">>", "<", ">", NULL};
	char **splited = my_split(line, charset);
	char **result;
	int res_ind = 0;
	int	size = 0;

	while (splited[size])
		size++;
	result = malloc(sizeof(char *) * (size + 1));
	for (int i = 0; splited[i]; i++)
	{
		if (is_equal(splited[i], "<<") || is_equal(splited[i], ">>") || is_equal(splited[i], "<") || is_equal(splited[i], ">"))
		{
			result[res_ind++] = ft_strjoin(splited[i], splited[i + 1]);
			i++;
		}
		else
		{
			result[res_ind++] = ft_strdup(splited[i]);
		}
	}
	result[res_ind] = NULL;
	
	for (int j = 0; splited[j]; j++)
		free(splited[j]);
	free(splited);
	
	return (result);
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
