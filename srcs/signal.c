/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyu <minkyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:53:26 by minkyuki          #+#    #+#             */
/*   Updated: 2023/01/31 20:08:36 by minkyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_handler(void (*sint_handler)(int s), void (*squit_handler)(int s))
{
	if (sint_handler)
		signal(SIGINT, sint_handler);
	else
		signal(SIGINT, SIG_IGN);
	if (squit_handler)
		signal(SIGQUIT, squit_handler);
	else
		signal(SIGQUIT, SIG_IGN);
}
// 시그널 핸들러를 설정합니다. NULL이 주어진 경우 해당 시그널을 무시합니다

void	set_signal(int sigint, int sigquit)
{
	if (sigint == DFL)
		signal(SIGINT, SIG_DFL);
	else if (sigint == IGN)
		signal(SIGINT, SIG_IGN);
	if (sigquit == DFL)
		signal(SIGQUIT, SIG_DFL);
	else if (sigquit == IGN)
		signal(SIGQUIT, SIG_IGN);
}

void	print_prompt(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}
// 시그널 입력시 프롬포트를 출력합니다

void	print_newline(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT)
		printf("Quit: 3\n");
	rl_on_new_line();
	rl_replace_line("", 1);
}
// 시그널 입력시 개행과 메시지를 출력합니다

void	quite(int sig)
{
	(void)sig;
	rl_replace_line("", 1);
}
// 시그널을 무시합니다