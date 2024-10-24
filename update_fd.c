#include "parser.h"

/* Opens the file depending on redir_type
 * closes earlier fd if its > 2 */
int	open_file(t_node *node, rtype redir_type, char *file)
{
	if (redir_type == NONE)
		return (0);
	if (redir_type == HEREDOC)
	{
		printf("not implemented\n");
		return (0);
	}
	if (redir_type == IN || redir_type == HEREDOC)
	{
		if (node->fdin > 2)
			close(node->fdin);
		if (redir_type == IN)
			node->fdin = open(file, O_RDONLY);
		if (node->fdin < 0)
		{
			printf("Failed to open file: %s\n", file);
			return (0);
		}
		return (1);
	}
	if (node->fdout > 2)
		close(node->fdout);
	if (redir_type == OUT)
		node->fdout = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		node->fdout = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (node->fdout < 0)
	{
		printf("Failed to open file: %s\n", file);
		return (0);
	}
	return (1);
}

/* Returns the name of the file
 * if its quoted, trims the quotes */
char	*get_file(char *input)
{
	char	*ptr;
	if (*input == '\'' || *input == '\"') // file name is quoted ?
		return (ft_substr(input, 1, ft_strchr(input + 1, *input) - input - 1)); // trim quotes
	ptr = input;
	while (*ptr && ft_strchr("@#$%\'\" |<>", *ptr) == NULL)
		ptr++;
	return (ft_substr(input, 0, ptr - input));
}

rtype	get_type(char *input)
{
	if (input[0] != input[1] && ft_strchr("<>", input[1])) // chars are not same, but both are redir symbols (<> or ><)
		return (NONE);
	if (input[0] == '<')
	{
		if (input[1] == '<')
			return (HEREDOC);
		else
			return (IN);
	}
	if (input[1] == '>')
		return (APPEND);
	return (OUT);
}

/* updates nodes fdin or fdout
 * returns number of chars iterated
 * error, returns 0 */
int	update_fd(t_node *node, char *input)
{
	int		i; // current index
	rtype	redir_type;
	char	*file;

	i = 0;
	redir_type = get_type(input);
	while (input[i] && ft_strchr("<>", input[i])) // skip redir symbols
		i++;
	while (input[i] == ' ') // then spaces
		i++;
	file = get_file(&input[i]);
	if (ft_strchr("\'\"", input[i])) // filname is in quotes
		i += 2;
	if (file == NULL)
		return (0);
	if (ft_strlen(file) == 0 || ft_strlen(file) > 255) // is there a max limit really?
	{
		free(file);
		return (0);
	}
	if (open_file(node, redir_type, file) == 0)
		return (0);
	i += ft_strlen(file);
	free(file);
	return (i);
}
