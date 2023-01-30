#include "../includes/minishell.h"

void	set_signal(int sigint, int sigquit)
{
	if (sigint == DFL)
		signal(SIGINT, SIG_DFL);
	else if (sigint == IGN)
		signal(SIGINT, SIG_IGN);
	else if (sigint == HAN)
		signal(SIGINT, signal_handler);
	if (sigquit == DFL)
		signal(SIGQUIT, SIG_DFL);
	else if (sigquit == IGN)
		signal(SIGQUIT, SIG_IGN);
	else if (sigquit == HAN)
		signal(SIGQUIT, signal_handler);
}

void	signal_handler(int sig)
{
	struct termios	term;

	(void)sig;
	tcgetattr(STDIN, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN, TCSANOW, &term);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}