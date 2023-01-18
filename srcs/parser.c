#include "../includes/minishell.h"
/*
 * cmd 구조체 : [0] input commands, [1] command type, [2] count redirect units, [3] count pipes, [4] next commnad addr.
 * cmd 구조체의 input에 적절히 파싱한 2차원배열 문자열을 저장해야 한다.
 * cmd 구조체의 type에 command type을 지정한다. {word, pipeline, redirect}
 * cmd 구조체에 전체 pipe 개수를 저장한다.
 * 파싱 단계 :
 			1. 한줄 읽기
			2. 문법 검사 (에러처리) (ex. ;, 리다이렉트 인자가 없는 경우)
			3. 따옴표 안쪽이 아닌 스페이스로 명령 구분
			4. 쌍따옴표 안에서 이스케이프로 작동한 \ 제거
			5. 환경변수($) 고려
			6. CMD 단위 구분 : |, EOF 	
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

char	*parsing_word(char *line)
{
	struct stat	stat_buf;
	char		**token;
	char		*tmp;
	char		*cmd_path;
	int			i;

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

/*
 * cmd 구조체의 input에 적절히 파싱한 명령어 토큰들을 2차원배열 문자열로 저장해야 한다.
 *
 * @param	: 
 * @return	:
*/

int	count_space(char *line)
{
	int	cnt;

	cnt = 0;
	while (*line)
	{
		if (*line == ' ')
		{
			while (*line != ' ')
				line++;
			if (*line != '\0') //마지막에 space가 오는 경우 카운트하지 않음
				cnt++;
		}
		line++;
	}
	return (cnt);
}

int	count_pipe(char *line)
{
	int	cnt;

	cnt = 0;
	while (*line)
	{
		if (*line == '|')
		{
			while (*line == ' ')
				line++;
			if (*line == '|')
				return (-1); // pipe 에러처리
			cnt++;
		}
	}
	return (cnt);
}

char	**get_cmd_token(char *line)
{
	char	**cmds;
	int		cnt_pipe;

	cnt_pipe = count_pipe(line);
	cmds = (char **)malloc(sizeof(char *) * (cnt_pipe + 2)); // num of pipe = (num of pipe + 1) ,NULL
	if (!cmd)
		return (0);
	//CMD, BUILTIN, REDIRECTION 구분
	while (line[++i])
	{
		if ()
	}
	
}

// quote 홀수이면 -1 반환, 짝수면 1 반환
int	check_quote(char *line)
{
	int	cnt_quote_s;
	int cnt_quote_b;

	cnt_quote_s = 0;
	cnt_quote_b = 0;
	while (*line)
	{
		if (*line == '\'')
			cnt_quote_s++;
		if (*line == '"')
			cnt_quote_b++;
		else if (*line == '|')
		{
			if (cnt_quote_s % 2 == 1 || cnt_quote_b % 2 == 1)
				return (-1);
			cnt_quote = 0;
		}
	}
}