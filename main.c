/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:26:06 by minkyu            #+#    #+#             */
/*   Updated: 2023/02/02 16:56:10 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/process.h"

t_env	*g_env;
static void	run_minishell(void);

// void	print_cmd(t_cmd *cmd)
// {
// 	char **input;

// 	while (cmd)
// 	{ 
// 		printf("================\n");
// 		input= cmd->input;
// 		printf("input : \n");
// 		while (*input)
// 		{
// 			printf("%s\n", *input);
// 			input++;
// 		}
// 		printf("type : %d\n", cmd->type);
// 		printf("pipe_cnt : %d\n", cmd->pipe_cnt);
// 		printf("unit_cnt : %d\n", cmd->unit_cnt);
// 		cmd = cmd->next;
// 		printf("================\n");
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	set_envlist(envp);
	run_minishell();
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
