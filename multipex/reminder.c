/*	for (int i = 0; cmd[i].index >= 0; i++)
	{
		printf("cmd %d -----------\n", i);
		for (int j = 0; cmd[i].cmd[j]; j ++)
			printf("%s\n", cmd[i].cmd[j]);
		printf("----\n\n");
	}







//-------------------------------------------------   child process buisness
	pid = fork(); // div process
	if (pid == 0) // == 0 -> child
		sub_process(fd, &file1, paths, cmd1, env, 1) 
		// prep pour execve + execve
	else // -> parent
	{
		pid = fork(); // div process
		if (pid == 0) // -> child
			sub_process(fd, &file2, paths, cmd2, env, 2); 
			// NB execve quit le process automatiquement 
			//pas besoin de exit à la sortie d'un child
		else
			waitpid(pid, NULL, 1); // wait child to terminate
	}

	STDIN_FILENO = dup(stdin_backup);
	STDOUT_FILENO = dup(stdoud_backup);
//libéré délivréééééé ------------------------------------  il a free il a tout compris
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






int		ft_double_strlen(char **str)
{
	int	i;
	int j;
	int total;

	i = 0;
	j = 0;
	total = 0;
	while (str[i])
	{
		while (str[i][j])
		{
			j++;
			total ++;
		}
		total ++;
		j = 0;
		i++;
	}
	return (total);
}

char	*reverse_split(char **s)
{
	int i;
	int j;
	int k;
	int size;
	char *str;

	i = 0;
	j = 0;
	k = 0;
	size = ft_double_strlen(s);
	str = (char *)calloc(size + 1, sizeof(char));
	while (s[i])
	{
		while (s[i][j])
			str[k++] = s[i][j++];
		if (s[i + 1])
			str[k++] = ' ';
		j = 0;
		i++;
	}
	return (str);
}

int	ft_strlen_cmd(char *s)
{
	int i;

	i = 0;
	while (s[i] && s[i] != '|')
		i++;
	return (i);
}

char *ft_strdup_cmd(char *s, int turn)
{
	int i;
	int j;
	int size;
	char *str;

	i = 0;
	j = 0;
	while (turn != 0)
	{
		if (s[i] == '|')
			turn--;
		i++;
	}
	size = ft_strlen_cmd(&s[i]);
	str = (char *)calloc(size + 1, sizeof(char));
	while (s[i + j] && s[i + j] != '|')
	{
		str[j] = s[i + j];
		j++;
	}
	str[j] = 0;
	printf("-->%s\n", str);
	return (str);
}


*/