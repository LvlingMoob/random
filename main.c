#include "minishell.h"

/*useless utils plus ou moins*/
int	str_err(char *str, int ret)
{
	printf("%s\n", str);
	return ret;
}

/*strncmp sur n caracs*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptrs1;
	unsigned char	*ptrs2;

	i = 0;
	ptrs1 = (unsigned char *)s1;
	ptrs2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n - 1 && ptrs1[i] && ptrs2[i] && ptrs1[i] == ptrs2[i])
		i++;
	return (ptrs1[i] - ptrs2[i]);
}

/*trouce un string dans uen chaine de caractere*/
int ft_strchr_str(const char *s, const char *seek)
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

/* -------------------------------------------------------------------------------------- child process handler*/
void	 sub_process(int *fd, int *file, char **paths, char **cmd, char **env, int src)
{
	int findit;
	char *tmp_seek_cmd;
	char *tmp;

	findit = 0; // booléen :  je cherche un path 0 si non trouvé et 1 si trouvé
	for (int i = 0; paths[i]; i++)
	{
		if (ft_strchr_str(paths[i], "bin")) // strchr mais avec un string plutot qu'un caractère
		{
			tmp = ft_strjoin("/", cmd[0]); // adress des bin ne se finit pas pr '/' donc ajourt de / devant la commande
			tmp_seek_cmd = ft_strjoin(paths[i], tmp); // path/adresse/bin/commande
			if (!access(tmp_seek_cmd, X_OK)) // so acces à la commande en éxécution 
			{
				findit = i; // trouvé
				free(tmp);
				break ; // out
			}
			free(tmp_seek_cmd);
			free(tmp);
		}
	}
	if (src == 1)
	{
		close(fd[0]); // on est en écriture pas besoin de lire close fd[0]
		
		dup2(*file, 0); // file 1 devient l'entrée standart 
		dup2(fd[1], 1); // fd[1] devient la sortie standart
		
		close(*file); // dup = duplicate -> delete originaux
		close(fd[1]); // idem

		execve(tmp_seek_cmd, cmd, env); //exec cmd
	}
	else
	{
		close(fd[1]); // on est en lecture pas besoin d ecrire close fd[1] (dans pipe)
		
		dup2(fd[0], 0); // file 1 devient l'entrée standart
		dup2(*file, 1); // fd[1] devient la sortie standart
		
		close(*file); // dup = duplicate -> delete originaux
		close(fd[0]); // idem

		execve(tmp_seek_cmd, cmd, env); //exec cmd
	}
}

int main(int argc, char **argv, char **env)
{
/*variables declaration*/
	t_cmd	*cmd;
	char	**paths;
	int		*file;
	int		nbr;

	int pid;

	int fd[2];
	int stdin_backup;
	int stdoud_backup;

//------------------------------------------------    fd handler File Directory
	pipe(fd); // fd[0] = read  fd[1] = write
	stdin_backup = dup(STDIN_FILENO); // backup de stdin
	stdoud_backup = dup(STDOUT_FILENO); // backup de stdout 
	/*back ups useless la mais toujours bon de le faire juste au cas ou */

//------------------------------------------------    char ** buisness
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++; // get to path var dans env
	paths = ft_split(*env + 5, ':'); // + 5 pour passer le égal
	
	for (int i = 0; argv[i]; i ++)
	{
		if (*argv[i] == '|')
			nbr++;
	}
	cmd = (char **)calloc(nbr + 1, sizeof(char *));
	cmd = ft_split(argv[2], ' ');

//-------------------------------------------------   child process buisness
	pid = fork(); // div process
	if (pid == 0) // == 0 -> child
		sub_process(fd, &file1, paths, cmd1, env, 1) // prep pour execve + execve
	else // -> parent
	{
		pid = fork(); // div process
		if (pid == 0) // -> child
			sub_process(fd, &file2, paths, cmd2, env, 2); // NB execve quit le process automatiquement pas besoin de exit à la sortie d'un child
		else
			waitpid(pid, NULL, 1); // wait child to terminate
	}

	STDIN_FILENO = dup(stdin_backup);
	STDOUT_FILENO = dup(stdoud_backup);
/*libéré délivréééééé ------------------------------------*/ // il a free il a tout compris
	for (int i = 0; paths[i]; i++)
		free(paths[i]);
	for (int i = 0; cmd1[i]; i++)
		free(cmd1[i]);
	for (int i = 0; cmd2[i]; i++)
		free(cmd2[i]);

	free(paths);
	free(cmd1);
	free(cmd2);
	close(file1);
	close(file2);
	close(stdin_backup);
	close(stdoud_backup);
	return 0;
}
