/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:49:48 by bojung            #+#    #+#             */
/*   Updated: 2023/02/06 15:09:15 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

t_cmd	*get_unit_token(char *line)
{
	t_cmd	*cmd;
	char	**token;
	char	**temp;

	while (*line == ' ')
		line++;
	if (!*line)
		return (0);
	token = get_space_token(line);
	temp = token;
	token = get_cmd_token(temp);
	free_2d_arr(temp);
	if (check_error(token) < 0)
	{
		free_2d_arr(token);
		return (0);
	}
	token = check_path(token);
	cmd = get_cmd_info(token);
	free_2d_arr(token);
	return (cmd);
}

t_cmd	*get_cmd_info(char **token)
{
	t_cmd	*cmd;
	t_cmd	*head;
	int		p_cnt;
	int		unit;

	unit = 0;
	cmd = cmd_lstinit();
	head = cmd;
	p_cnt = cnt_pipe(token);
	init_input(cmd, token, unit);
	while (cmd)
	{
		init_type(cmd);
		cmd->pipe_cnt = p_cnt;
		remove_quotes(cmd->input);
		cmd = cmd->next;
	}
	return (head);
}

void	init_input(t_cmd *cmd, char **token, int unit)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		cmd->unit_cnt = unit;
		if (is_cmd(token[i], 0) > 0)
		{
			cmd = init_input_util(cmd, token, &i, &unit);
			token += i;
			i = -1;
			if (token[i + 1])
			{
				cmd_lstadd(cmd);
				cmd = cmd->next;
			}
		}
	}
	if (cmd->input == NULL)
	{
		cmd->unit_cnt = unit;
		cmd->input = ft_2d_strndup(token, i);
	}
}

t_cmd	*init_input_util(t_cmd *cmd, char **token, int *i, int *unit)
{
	if (*i != 0)
	{
		cmd->input = ft_2d_strndup(token, *i);
		cmd_lstadd(cmd);
		cmd = cmd->next;
		cmd->unit_cnt = *unit;
	}
	if (is_cmd(token[*i], 0) >= 2)
	{
		cmd->input = ft_2d_strndup(token + *i, 2);
		*i += 2;
	}
	else if (is_cmd(token[*i], 0) == 1)
	{
		cmd->input = ft_2d_strndup(token + *i, 1);
		(*unit)++;
		(*i)++;
	}
	return (cmd);
}

void	init_type(t_cmd *cmd)
{
	int	cmd_flag;

	while (cmd)
	{
		cmd_flag = is_cmd(cmd->input[0], 0);
		if (cmd_flag > 0)
		{
			if (cmd_flag == 1)
				cmd->type = pipeline;
			else if (cmd_flag > 1)
				cmd->type = redirect;
			else
				cmd->type = word;
		}
		else
			cmd->type = word;
		cmd = cmd->next;
	}
}
