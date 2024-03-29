/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 13:28:02 by bojung            #+#    #+#             */
/*   Updated: 2023/02/01 12:00:57 by minkyuki         ###   ########.fr       */
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

void	remove_quotes(char **input)
{
	char	*temp;

	while (*input)
	{
		temp = *input;
		*input = no_quote_strdup(*input);
		input++;
		free(temp);
	}
}

int	cnt_pipe(char **token)
{
	int	i;
	int	cnt;

	cnt = 0;
	while (*token)
	{
		i = 0;
		while ((*token)[i])
		{
			if ((*token)[i] == '|' && is_in_quote(*token, i) == NONE)
				cnt++;
			i++;
		}
		token++;
	}
	return (cnt);
}
