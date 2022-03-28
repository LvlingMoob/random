# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

typedef struct s_cmd
{
	char	**args;
}				t_cmd;

int	g_ret = 0;

void	fatal_error()
{
	write(2, "error : fatal\n", 14);
	exit(EXIT_FAILURE);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*new_str;

	new_str = malloc(sizeof(char) * ft_strlen(str));
	if (!new_str)
		fatal_error();
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

void	init_cmd(char **argv, int start, int i)
{
	int	j;

	j = start;
	while (j < i)
	{
		j++;
	}
}

void	to_exec_till_i(char **argv, char **env, int start, int i)
{
	int		j;
	int 	pipes;
	t_cmd	*cmd;

	j = start;
	pipes = 0;
	if (!args)
		fatal_error();
	while (j < i)
	{
		if (argv[j] && !strcmp(";", argv[j]))
			pipes++;
		j++;
	}
	cmd = malloc((pipes + 1) * sizeof(t_cmd));
	init_cmd(&cmd);
}

void	delimit_cmd(char **argv, char **env)
{
	static int	i = 1;
	int start;

	start = i;
	while (argv[i] && strcmp(";", argv[i]))
		i++;
	to_exec_till_i(argv, env, start, i);
	if (!argv[i])
		return ;
	i++;
	if (argv[i])
		delimit_cmd(argv, env);
}

int	main(int argc, char **argv, char **env)
{
	delimit_cmd(argv, env);
	return (g_ret);
}
