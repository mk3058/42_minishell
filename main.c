/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:26:06 by minkyu            #+#    #+#             */
/*   Updated: 2023/02/01 16:41:52 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/process.h"

t_env *g_env;

int main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	*line;

	(void)argc;
	(void)argv;
	set_envlist(envp);
	while (1)
	{
		set_echoctl(0);
		set_handler(print_prompt, NULL);
		line = readline("minishell> ");
		if (line)
		{
			if (line[0] != '\0')
				add_history(line);
			cmd = get_unit_token(line);
			if (!cmd)
				continue ;
			free(line);
			line = NULL;
			process(cmd);
		}
		else
		{
			printf("exit\n");
			break ;
		}
	}
}
