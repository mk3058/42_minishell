/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkyuki <minkyuki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:53:26 by minkyuki          #+#    #+#             */
/*   Updated: 2023/02/08 17:21:54 by minkyuki         ###   ########.fr       */
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

void	print_newline(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		*(g_env->exit_stat) = 130;
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
		*(g_env->exit_stat) = 131;
	}
	rl_on_new_line();
	rl_replace_line("", 1);
}

void	quiet(int sig)
{
	if (sig == SIGINT)
		*(g_env->exit_stat) = 130;
	else if (sig == SIGQUIT)
		*(g_env->exit_stat) = 131;
	rl_replace_line("", 1);
}
