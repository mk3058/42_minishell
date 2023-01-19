#include "../includes/minishell.h"

# define NONE	0
# define DQUOTE 1
# define SQUOTE 2
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

// 사용하고 남은 2차원 배열 처리
void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

// 환경변수때문에 squote dquote 구분함
int	is_in_quote(char *line, int idx)
{
	int	i;
	int	quote_flag;

	quote_flag = NONE;
	i = -1;
	while (++i < idx)
	{
		if (line[i] == '"')
		{
			if (quote_flag == NONE)
				quote_flag = DQUOTE;
			else
				quote_flag = NONE;
		}
		if (line[i] == '\'')
		{
			if (quote_flag == NONE)
				quote_flag = SQUOTE;
			else
				quote_flag = NONE;
		}
	}
	return (quote_flag);
}

int	cnt_space(char *line)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (line[i])
	{
		if (!is_in_quote(line, i) && line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
			if (line[i] != '\0') //마지막에 space가 오는 경우 카운트하지 않음
				cnt++;
		}
		i++;
	}
	return (cnt);
}

// space 단위로 자른 토큰을 2d arr로 반환
char	**get_space_token(char *line)
{
	char	**token;
	int		i;
	int		start;
	int		idx;

	start = 0;
	i = 0;
	idx = 0;
	token = (char **)malloc(sizeof(char *) * (cnt_space(line) + 2));
	while (line[i])
	{
		if (!is_in_quote(line, i) && line[i] == ' ')
		{
			token[idx] = ft_substr(line, start, i - start);
			while (line[i] == ' ')
				i++;
			if (line[i] == '\0')
				break ;
			start = i;
			idx++;
		}
		i++;
	}
	if (i > 0)
		token[idx++] = ft_substr(line, start, i - start);
	token[idx] = NULL;
	return (token);
}

/* 
 * 먼저 따옴표를 확인하며 공백으로 토큰을 나누고, <<, <, >, | 등을 라인별로 확인 후 처리
 * 1. 공백 개수, " ' 고려하여 확인
 * 2. redirect, pipe 토큰화
 * @return **unit_token
 * 개발중
*/
char	**get_unit_token(char *line)
{
	char	**token;
	int	i = 0;

	// test용 임시 코드
	token = get_space_token(line);
	while (token[i])
	{
		printf("token[%d] = %s\n", i, token[i]);
		i++;
	}
	return (0);
}
