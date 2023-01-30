#include "includes/minishell.h"

t_cmd *test_parse(char *line, int *exit_stat); //////////////////////////
#include "includes/process.h"

t_env *g_env;

/* ***** 수정사항*****
 * (X) ctrl + c signal 전송시 간헐적으로 prompt가 여러번 출력됨 -> 실행중인 프로세스 수 만큼 출력되는듯?
 * (O) ls t | grep test | cat -e 등 명령어에서 오류 메시지가 여러번 출력됨 -> 테스트 파서 문제였음
 * (X) prompt에서 ctrl + c 입력시 처음에 ^C 반향이 출력됨
 */

int main()
{
	char	*line;
	t_cmd	*cmd;
	int		*exit_stat = malloc(sizeof(int));

	set_signal(HAN, IGN);
	*exit_stat = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (line[0] != '\0')
				add_history(line);
			cmd = test_parse(line, exit_stat);
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
