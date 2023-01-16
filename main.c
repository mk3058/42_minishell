#include "includes/minishell.h"

void	signal_handler(int sig);

int main()
{
	char	*line;

	signal(SIGINT, signal_handler);
	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			add_history(line);
			//파싱?
			free(line);
			line = NULL;
		}
		else
		{
			break ;
		}
	}
}

void	signal_handler(int sig)
{
	printf("\n");
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}
