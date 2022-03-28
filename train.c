#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

ft_putstr_err(char *str)
{
	while(*str)
		write(2, str++, 1);
}

int	ft_exec(char *argv[], int i, int tmp_fd, char *env[])
{
	argv[i];
	close(tmp_fd);
	execve(argv[0], argv, env);
	// err
	return (1);
}

int main(int argc, char *argv[], char *env[])
{
	int i;
	int pid;
	int fd[2];
	int tmp_fd;

	i = 0;
	pid= 0;
	tmp_fd = dup(STDIN_FILENO);

	while (argv[i], && argv[i + 1])
	{
		argv = &argv[i + 1];
		i = 0;
	}
}
