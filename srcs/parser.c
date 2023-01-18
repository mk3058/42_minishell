#include "includes/minishell.h"

/*
 * cmd 구조체 : [0] input commands, [1] command type, [2] count redirect units, [3] count pipes, [4] next commnad addr.
 * cmd 구조체의 input에 적절히 파싱한 2차원배열 문자열을 저장해야 한다.
 * cmd 구조체의 type에 command type을 지정한다. {word, pipeline, redirect}
 * cmd 구조체에 전체 pipe 개수를 저장한다.
 * 파싱 단계 :
 			1. 한줄 읽기
			2. 따옴표 안쪽이 아닌 스페이스로 명령 구분
			3. 쌍따옴표 안에서 이스케이프로 작동한 \ 제거
			4. 환경변수($) 고려
			5. CMD 단위 구분 : |, ;, EOF 
			
*/

static void free_all(char *cmd_path, char **token)
{
	int	i;

	i = 0;
	while(token[i])
	{
		free(token[i]);
		i++;
	}
	free(token);
	free(cmd_path);
}

char	*parsing(char *line)
{
	struct stat stat_buf;
	char	**token;
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = -1;
	token = ft_split(getenv("PATH"), ':');
	while (token[++i])
	{
		tmp = ft_strjoin(token[i], "/");
		cmd_path = ft_strjoin(tmp, line);
		free(tmp);
		if (!stat(cmd_path, &stat_buf))
			break ;
		free(cmd_path);
		cmd_path = NULL;
	}
	free_all(cmd_path, token);
	return (cmd_path);
}
