#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>

enum e_type
{
	CMD = 1,
	PIPE,
	STDIN,
	STDOUT
};

typedef struct s_cmd
{
	int		index;
	char	**cmd;
	int		src;
	int		dest;
}				t_cmd;

typedef struct s_files
{
	int	fd[2];
	int	ext_file;
	int	stdin_backup;
	int	stdoud_backup;
}				t_files;

char	**ft_split(char const *s, char c);
int		ft_strlen(char const *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*reverse_split(char **s, char c);
int		nbr_of_pipe(char *str_argv);
void	args_to_cmds(t_cmd *cmd, char **argv);

#endif
