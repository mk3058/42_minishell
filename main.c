#include "includes/minishell.h"

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
			//parsing
			//get_unit_token(line);
			printf("%s\n", get_env("PATH"));
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
