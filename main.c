#include "includes/minishell.h"

t_env *env;

int main()
{
	char	*line;

	set_signal(HAN, IGN);
	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (line[0] != '\0')
				add_history(line);
			//파싱?
			free(line);
			line = NULL;
		}
		else
		{
			printf("\x1b[1A\033[11Cexit\n");
			break ;
		}
	}
}
