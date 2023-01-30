#include "includes/minishell.h"
#include "includes/process.h"

static void	set_exit_stat(t_cmd *cmd, int *exit_stat);

t_env *g_env;

int main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	char	*line;
	int		exit_stat;

	(void)argc;
	(void)argv;
	set_envlist(envp);
	while (1)
	{
		set_signal(HAN, IGN);
		line = readline("minishell> ");
		if (line)
		{
			if (line[0] != '\0')
				add_history(line);
			cmd = get_unit_token(line);
			if (!cmd)
				continue ;
			set_exit_stat(cmd, &exit_stat);
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

static void	set_exit_stat(t_cmd *cmd, int *exit_stat)
{
	while (cmd)
	{
		cmd->exit_stat = exit_stat;
		cmd = cmd->next;
	}
}
