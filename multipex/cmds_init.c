#include "minishell.h"

void	args_to_cmds(t_cmd *cmd, char **argv)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	j = 0;
	nb = 0;
	cmd[j].src = STDIN;
	while (argv[i])
	{
		if (!ft_strncmp(argv[i], "|", 1))
		{
			nb++;
			cmd[j].index = nb;
			j++;
			cmd[j].src = PIPE;
			i++;
		}
		cmd[j].cmd = ft_split(argv[i], ' ');
		cmd[j].dest = PIPE;
		i++;
	}
	cmd[j].dest = STDOUT;
	cmd[j].index = ++nb;
}

/*
//backup
void	args_to_cmds(t_cmd *cmd, char **argv)
{
	int i;
	int j;
	int k;
	int turn;
	int	nb;

	i = 0;
	j = 0;
	k = 0;
	nb = 0;
	turn = 0;
	cmd[j].src = STDIN;
	while (argv[i])
	{
//		cmd[j].cmd = (char **)realloc(cmd[j].cmd, sizeof(char *) * (turn + 2));
		if (!ft_strncmp(argv[i], "|", 1))
		{
			nb++;
			cmd[j].index = nb;
			j++;
			cmd[j].src = PIPE;
			// -----------------------------------------------   pipe part
			cmd[j].cmd = (char **)calloc(2, sizeof(char *));
			cmd[j].cmd[0] = ft_strdup(argv[i]);
			cmd[j].index = 0;
			cmd[j].src = -1;
			cmd[j].dest = -1;
			j++;
			// ---------------
			turn = 0;
//			cmd[j].cmd = (char **)realloc(cmd[j].cmd, sizeof(char *) * (turn + 2));
			k = 0;
			i++;
		}
		cmd[j].cmd = ft_split(argv[i], ' ');
		cmd[j].dest = PIPE;
		i++;
		turn ++;
	}
	cmd[j].dest = STDOUT;
	cmd[j].index = ++nb;
	i = 0;
	while (i <= j)
		i++;
	cmd[i].index = -1;
}
*/