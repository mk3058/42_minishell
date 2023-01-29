#include "includes/minishell.h"

t_cmd *test_parse(void); //////////////////////////
#include "includes/process.h"

t_env *g_env;

int main()
{
	char	*line;
	t_cmd	*cmd;

	set_signal(HAN, IGN);
	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (line[0] != '\0')
				add_history(line);
			cmd = test_parse();
			free(line);
			line = NULL;
			process(cmd);
		}
		else
		{
			printf("\x1b[1A\033[11Cexit\n");
			break ;
		}
	}
}
