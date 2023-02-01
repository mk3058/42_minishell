/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 14:28:58 by minkyuki          #+#    #+#             */
/*   Updated: 2023/02/01 15:26:02 by minkyuki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_echoctl(int mode)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (mode)
		term.c_lflag |= (ECHOCTL);
	else
		term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
// 터미널의 시그널 반향 출력을 설정합니다 
// mode = 1일경우 반향이 출력되고 0이면 무시됩니다

void	heredoc_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	exit(1);
}

void	heredoc_quiet(int sig)
{
	if (sig == SIGINT)
		*(g_env->exit_stat) = 1;
	rl_replace_line("", 1);
}
