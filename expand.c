#include "parser.h"

char	*getkey(char *input)
{
	char	*ptr;

	ptr = input;
	if (ft_isalpha(*ptr) == 0 && *ptr != '|') // not ok
		return (ft_strdup("$"));
	while (ft_isalnum(*ptr) || *ptr == '|')
		ptr++;
	return (ft_substr(input, 0, ptr - input));
}

int	expand(char **arg, char *input)
{
	char	*key;
	int		i;

	i = 1;
	key = getkey(&input[i]);
	if (key == NULL)
		return (0);
	join(arg, getenv(key));
	i += ft_strlen(key);
	free(key);
	return (i);
}
