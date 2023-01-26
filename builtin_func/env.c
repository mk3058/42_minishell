/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 21:46:24 by minkyu            #+#    #+#             */
/*   Updated: 2023/01/26 16:47:59 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtin.h"
#include "../includes/process.h"

static int	is_key_value_format(char *input);
static int	modify_env(t_cmd *cmd);
static void	env_print(void);

int	env(t_cmd *cmd)
{
	int		util_index;
	char	*cmd_path;

	util_index = modify_env(cmd);
	if (!cmd->input[util_index])
		env_print();
	else
	{
		cmd_path = find_path(cmd->input[util_index]);
		cmd->input[util_index] = ft_strdup(cmd_path);
		if (execve(cmd_path, cmd->input[util_index], env_to_array()) == -1)
			exit_err(NULL, NULL, NULL);
	}
	return (0);
}

static int	modify_env(t_cmd *cmd)
{
	char	**input;
	int		i;

	input = (cmd->input);
	i = 1;
	while (input[i] && is_key_value_format(input[i]))
	{
		add_env(input[i]);
		i++;
	}
	return (i);
}

static int	is_key_value_format(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (input[i] == '=')
			return (1);
	return (0);
}

static void	env_print(void)
{
	t_env	*tmp;

	tmp = g_env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
