/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 20:26:06 by minkyu            #+#    #+#             */
/*   Updated: 2023/02/01 12:02:15 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/process.h"

t_env *g_env;

/** here_doc
 * 시그널 처리 -> 자식 프로세스에서 처리하는걸로 바꿔야함
 * 환경변수 치환 전에 전처리 필요
 * 	-> 따옴표 존재하는 경우 ", ' 상관없이 하나만 제거하고 나머지는 limiter처리 
*/

/** exit_stat
 * 시그널 종료시 exit_stat에 해당 시그널 넘버가 더해져야 함
 * 	-> exit_stat 변수를 env 전역변수에 추가
*/

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
