#include "includes/minishell.h"

t_env *g_env;

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	set_envlist(envp);
	//printf("%s\n", get_env("PATH"));
	// while (*envp)
	// {
	// 	printf("%s\n", *envp);
	// 	envp++;
	// }
	
	char	*line;

	set_signal(HAN, IGN);
	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (line[0] != '\0')
				add_history(line);
				get_unit_token(line);
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
