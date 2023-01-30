#include "includes/minishell.h"

t_env *g_env;

int main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	*line;

	(void)argc;
	(void)argv;
	set_envlist(envp);
	set_signal(HAN, IGN);
	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (line[0] != '\0')
				add_history(line);
			cmd = get_unit_token(line);
			free(line);
			line = NULL;
			printf("==== exit_status : %d ====\n", *cmd->exit_stat);
			process(cmd);
		}
		else
		{
			printf("\x1b[1A\033[11Cexit\n");
			break ;
		}
	}
}
