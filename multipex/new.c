#include "minishell.h"

int	ft_strchr_str(const char *s, const char *seek)
{
	int				i;
	int				j;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	j = 0;
	s1 = (unsigned char *)s;
	s2 = (unsigned char *)seek;
	while (s1[i])
	{
		while (s1[i + j] == s2[j])
		{
			if (!s2[j] && !s1[i + j])
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

void	from_stdin_to_stdout(t_files *fdirectory)
{
	dup2(fdirectory->stdin_backup, 0);
	dup2(fdirectory->stdoud_backup, 1);
}

void	from_stdin_to_pipe(t_files *fdirectory)
{
	dup2(fdirectory->stdin_backup, 0);
	dup2(fdirectory->fd[1], 1);
}

void	from_pipe_to_pipe(t_files *fdirectory)
{
	dup2(fdirectory->fd[0], 0);
	dup2(fdirectory->fd[1], 1);
}

void	from_pipe_to_stdout(t_files *fdirectory)
{
	dup2(fdirectory->fd[0], 0);
	dup2(fdirectory->stdoud_backup, 1);
}

void	close_files(t_files *fdirectory)
{
	close(fdirectory->stdin_backup);
	close(fdirectory->stdoud_backup);
	close(fdirectory->fd[0]);
	close(fdirectory->fd[1]);
}

int	stdin_src(t_files *fdirectory, t_cmd *cmd, char **env, char *tmp_seek_cmd)
{
	if (cmd->dest == STDOUT)
	{
		from_stdin_to_stdout(fdirectory);
		return (execve(tmp_seek_cmd, cmd->cmd, env));
	}
	else if (cmd->dest == PIPE)
	{
		for (int i = 0; cmd->cmd[i]; i++)
			printf("%s\n", cmd->cmd[i]);
		printf("%s\n", tmp_seek_cmd);
		from_stdin_to_pipe(fdirectory);
		return (execve(tmp_seek_cmd, cmd->cmd, env));
	}
	return (-2);
}

int	pipe_src(t_files *fdirectory, t_cmd *cmd, char **env, char *tmp_seek_cmd)
{
	if (cmd->dest == STDOUT)
	{
		for (int i = 0; cmd->cmd[i]; i++)
			printf("%s\n", cmd->cmd[i]);
		from_pipe_to_stdout(fdirectory);
		return (execve(tmp_seek_cmd, cmd->cmd, env));
	}
	else if (cmd->dest == PIPE)
	{
		for (int i = 0; cmd->cmd[i]; i++)
			printf("%s\n", cmd->cmd[i]);
		from_pipe_to_pipe(fdirectory);
		return (execve(tmp_seek_cmd, cmd->cmd, env));
	}
	return (-2);
}

char	*find_cmd(char **paths, t_cmd *cmd)
{
	int		findit;
	char	*tmp_seek_cmd;
	char	*tmp;

	findit = 0;
	for (int i = 0; paths[i]; i++)
	{
		if (ft_strchr_str(paths[i], "bin"))
		{
			tmp = ft_strjoin("/", cmd->cmd[0]);
			tmp_seek_cmd = ft_strjoin(paths[i], tmp);
			printf("%s\n", tmp_seek_cmd);
			if (!access(tmp_seek_cmd, X_OK))
			{
				findit = i;
				free(tmp);
				break ;
			}
			free(tmp_seek_cmd);
			free(tmp);
		}
	}
	if (findit)
		return (tmp_seek_cmd);
	return (NULL);
}

int	sub_process(t_files *fdirectory, char **paths, t_cmd *cmd, char **env)
{
	char	*tmp_seek_cmd;

	tmp_seek_cmd = find_cmd(paths, cmd);
	if (tmp_seek_cmd)
	{
		if (cmd->src == STDIN)
			return (stdin_src(fdirectory, cmd, env, tmp_seek_cmd));
		else if (cmd->src == PIPE)
			return (pipe_src(fdirectory, cmd, env, tmp_seek_cmd));
		close_files(fdirectory);
	}
	else
	{
		close_files(fdirectory);
		for (int i = 0; paths[i]; i++)
			free(paths[i]);
		free(paths);
		return (0);
	}
	return (-2);
}

void	free_all(t_cmd *cmd, char **paths, char *str_argv)
{
	for (int i = 0; cmd[i].index > 0; i++)
	{
		for (int j = 0; cmd[i].cmd[j]; j ++)
			free(cmd[i].cmd[j]);
		free(cmd[i].cmd);
	}
	for (int i = 0; paths[i]; i++)
		free(paths[i]);
	free(str_argv);
	free(cmd);
	free(paths);
}

void	process(t_files *fdirectory, char **paths, t_cmd *cmd, char **env, char *str_argv)
{
	int	i;
	int	pid;

	i = 0;
	while (cmd[i].index > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (sub_process(fdirectory, paths, &cmd[i], env) <= 0)
			{
				free_all(cmd, paths, str_argv);
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		else
			waitpid(pid, NULL, 0);
		break ;
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	*cmd;
	char	*str_argv;
	char	**paths;
	t_files	fdirectory;

	pipe(fdirectory.fd);
	fdirectory.stdin_backup = dup(STDIN_FILENO);
	fdirectory.stdoud_backup = dup(STDOUT_FILENO);
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	paths = ft_split(*env + 5, ':');
	str_argv = reverse_split(argv, ' ');
	cmd = (t_cmd *)calloc(nbr_of_pipe(str_argv) + 2, sizeof(t_cmd));
	args_to_cmds(cmd, &argv[1]);
	process(&fdirectory, paths, cmd, env, str_argv);
	close_files(&fdirectory);
	free_all(cmd, paths, str_argv);
	return (0);
}
