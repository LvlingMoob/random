#include "minishell.h"

int	nbr_of_pipe(char *str_argv)
{
	int	res;

	res = 0;
	while (*str_argv)
	{
		str_argv++;
		if (*str_argv == '|')
			res++;
	}
	return (res);
}

int	ft_strlen_array(char **str)
{
	int	i;
	int	j;
	int	total;

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

char	*reverse_split(char **s, char c)
{
	int		i;
	int		j;
	int		k;
	int		size;
	char	*str;

	i = 0;
	j = 0;
	k = 0;
	size = ft_strlen_array(s);
	str = (char *)calloc(size + 1, sizeof(char));
	while (s[i])
	{
		while (s[i][j])
			str[k++] = s[i][j++];
		if (s[i + 1])
			str[k++] = c;
		j = 0;
		i++;
	}
	return (str);
}
