/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:26:06 by minkyu            #+#    #+#             */
/*   Updated: 2023/02/08 16:02:04 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/process.h"

t_env	*g_env;
static void	run_minishell(void);

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	set_envlist(envp);
	run_minishell();
	clear_history();
	destroy_env();
}

static void	run_minishell(void)
{
	char	*line;
	t_cmd	*cmd;

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
			free(line);
			line = NULL;
			if (cmd)
				process(cmd);
		}
		else
		{
			printf("exit\n");
			break ;
		}
	}
}
