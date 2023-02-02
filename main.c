/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:26:06 by minkyu            #+#    #+#             */
/*   Updated: 2023/02/02 21:31:28 by minkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/process.h"

t_env	*g_env;
static void	run_minishell(void);

/**
 * quotes 안에 있는 |, <<, <, >, >>를 special words로 인식함 
 * 	-> quote로 둘러쌓여 입력된 경우 문법 검사에서 안걸러짐
 * 		- echo '|' , cat '<<' 등등
 * 
 * empty cmd, space, echo 등등 사용시 leak 발생
 * 	-> 어디서 나는건지 확인해봐야할듯
*/

void	print_cmd(t_cmd *cmd)
{
	char **input;

	while (cmd)
	{ 
		printf("================\n");
		input= cmd->input;
		printf("input : \n");
		while (*input)
		{
			printf("%s\n", *input);
			input++;
		}
		printf("type : %d\n", cmd->type);
		printf("pipe_cnt : %d\n", cmd->pipe_cnt);
		printf("unit_cnt : %d\n", cmd->unit_cnt);
		cmd = cmd->next;
		printf("================\n");
	}
}

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
			print_cmd(cmd);
			process(cmd);
		}
		else
		{
			printf("exit\n");
			break ;
		}
	}
}
