#include "minishell.h"

/*pour split*/
static int	is_delimiter(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

/*pour split*/
static int	words_count(char const *s, char sep, int *x, int *y)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	*x = -1;
	*y = 0;
	while (s[i])
	{
		if (!is_delimiter(s[i], sep))
		{
			while (s[i] && !is_delimiter(s[i], sep))
				i++;
			count++;
		}
		while (s[i] && is_delimiter(s[i], sep))
			i++;
	}
	return (count);
}

/*strdup pour split*/
static char	*ft_strdup_custom(char const *s, char c, int *j)
{
	int		i;
	int		k;
	char	*st;

	i = 0;
	k = 0;
	while (!is_delimiter(s[i], c) && s[i])
		i++;
	st = (char *)calloc(i + 1, sizeof(char));
	if (!st)
		return (NULL);
	while (k < i)
	{
		st[k] = s[k];
		k++;
	}
	st[k] = '\0';
	while (is_delimiter(s[i], c) && s[i])
		i++;
	*j += i;
	return (st);
}

/*split basic*/
char	**ft_split(char const *s, char c)
{
	char	**str;
	int		count;
	int		i;
	int		j;

	if (!s)
		return (0);
	count = words_count(s, c, &i, &j);
	str = (char **)calloc(count + 1, sizeof(char *));
	if (!str)
		return (NULL);
	while (is_delimiter(s[j], c) && s[j])
		j++;
	while (++i < count && s[j])
		str[i] = ft_strdup_custom(&s[j], c, &j);
	str[i] = 0;
	return (str);
}
