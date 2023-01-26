#include "../includes/builtin.h"
#include "../includes/process.h"
#include <stdlib.h>

extern char **environ;
void	add_newnode(t_cmd *head, char **input, int pipe_cnt, int *exit_stat);

t_env *g_env;

int main()
{
	t_cmd	*head = malloc(sizeof(t_cmd));
	int		*exit_stat = malloc(sizeof(int));

	head->input = ft_split("env HOME=test echo !!!!!", ' ');
	head->type = word;
	head->pipe_cnt = 0;
	head->unit_cnt = 0;
	head->exit_stat = exit_stat;
	head->next = NULL;
	set_envlist(environ);
	//add_newnode(head, ft_split("env HOME=test", ' '), 0, exit_stat);
	process(head);
}

// void	add_newnode(t_cmd *head, char **input, int pipe_cnt, int *exit_stat)
// {
// 	static int	unit_cnt;
// 	t_cmd		*new;

// 	new = malloc(sizeof(t_cmd));
// 	new->input = input;
// 	new->pipe_cnt = pipe_cnt;
// 	new->unit_cnt = unit_cnt;
// 	if (**input == '|')
// 	{
// 		new->type = pipeline;
// 		unit_cnt++;
// 	}
// 	else if (**input == '<' || **input == '>')
// 		new->type = redirect;
// 	else
// 		new->type = word;
// 	new->exit_stat = exit_stat;
// 	new->next = NULL;
// 	if (head)
// 	{
// 		while (head->next)
// 			head = head->next;
// 		head->next = new;
// 	}
// 	else
// 		head = new;
// }