#include "pipex.h"

static char	**parse_envp(char **envp);
static char	*parse_cmd(char *cmd);
static void	free_all(char *cmd, char **env_path);
static char	*find_cmd_path(char	*cmd, char **envp);

void	execute_cmd(char **argv, char **envp, int cnt, int **fd)
{
	char	*path;
	char	**arg;
	int		argc;
	int		std_out;

	argc = 0;
	while (argv[argc])
		argc++;
	path = find_cmd_path(argv[cnt], envp);
	arg = ft_split(argv[cnt], ' ');
	free(arg[0]);
	arg[0] = ft_strdup(path);
	std_out = set_fd(argc, argv, fd, cnt - 2);
	if (execve(path, arg, envp) == -1)
	{
		dup2(std_out, STDOUT_FILENO);
		exit_err(strerror(errno), NULL, NULL);
	}
}

static char	*find_cmd_path(char	*cmd, char **envp)
{
	char	**env_path;
	char	*file_path;
	char	*cmd_tmp;
	int		i;

	i = -1;
	cmd_tmp = parse_cmd(cmd);
	if (access(cmd_tmp, R_OK | X_OK) == 0)
		return (cmd_tmp);
	env_path = parse_envp(envp);
	while (env_path[++i])
	{
		file_path = ft_strjoin(env_path[i], cmd_tmp);
		if (access(file_path, R_OK | X_OK) == 0)
		{
			free_all(cmd_tmp, env_path);
			return (file_path);
		}
		else
			free(file_path);
	}
	free_all(cmd_tmp, env_path);
	exit_err("command not found", NULL, cmd);
	return (NULL);
}

static char	**parse_envp(char **envp)
{
	int		i;
	char	*tmp;
	char	**env_path;

	i = 0;
	env_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (env_path[++i])
	{
		tmp = env_path[i];
		env_path[i] = ft_strjoin(env_path[i], "/");
		free(tmp);
	}
	return (env_path);
}

static char	*parse_cmd(char *cmd)
{
	char	*cmd_tmp;
	int		i;

	i = -1;
	cmd_tmp = ft_strdup(cmd);
	while (cmd_tmp[++i])
	{
		if (cmd_tmp[i] == ' ')
		{
			cmd_tmp[i] = '\0';
			break ;
		}
	}
	return (cmd_tmp);
}

static void	free_all(char *cmd, char **env_path)
{
	int	size;

	size = 0;
	while (env_path[size])
		size++;
	dealloc(env_path, size);
	free(cmd);
}