#include "parser.h"

int	join(char **str, char *s)
{
	char	*new;
	char	*old;
	int		i;
	int		j;

	if (s == NULL)
		return (1);
	old = *str;
	new = malloc(ft_strlen(old) + ft_strlen(s) + 1);
	if (new == NULL)
		return (0);
	i = 0;
	while (old[i])
	{
		new[i] = old[i];
		i++;
	}
	j = 0;
	while (s[j])
	{
		new[i] = s[j];
		i++;
		j++;
	}
	new[i] = '\0';
	*str = new;
	free(old);
	return (1);
}

/* add c to end of str */
int	append(char **str, char c)
{
	int		i;
	char	*new;

	new = malloc(ft_strlen(*str) + 2);
	if (new == NULL)
		return 0;
	i = 0;
	while ((*str)[i])
	{
		new[i] = (*str)[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	free(*str);
	*str = new;
	return (1);
}

int	arr_len(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}

/* Adds str to end of arr */
int	add(char ***arr, char *str)
{
	char	**new;
	char	**old;
	int		i;

	new = malloc((arr_len(*arr) + 2) * sizeof(char *));
	if (new == NULL)
		return (0);
	i = 0;
	old = *arr;
	while (old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i] = str;
	new[i + 1] = NULL;
	free(old);
	*arr = new;
	return (1);
}
