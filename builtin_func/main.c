#include "../includes/builtin.h"

extern char **environ;

t_env *g_env;

int main()
{
	t_cmd cmd;

	cmd.input = ft_split("export", ' ');
	cmd.next = NULL;
	cmd.pipe_cnt = 0;
	cmd.type = word;
	cmd.unit_cnt = 0;

	set_envlist(environ);
	export(&cmd);
	printf("\n-------------------------\n");

	cmd.input = ft_split("export testtesttest", ' ');
	export(&cmd);
	printf("\n-------------------------\n");

	cmd.input = ft_split("export", ' ');
	export(&cmd);
	printf("\n-------------------------\n");

	env();
	printf("\n-------------------------\n");

	pwd();
	printf("\n-------------------------\n");

	cmd.input = ft_split("echo test1test1test1", ' ');
	echo(&cmd);
	printf("\n-------------------------\n");

	cmd.input = ft_split("echo -nnnnnn test1test1test1", ' ');
	echo(&cmd);
	printf("\n-------------------------\n");

	cmd.input = ft_split("echo -nnnnm test1test1test1", ' ');
	echo(&cmd);
	printf("\n-------------------------\n");
}