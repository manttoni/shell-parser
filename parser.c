#include "parser.h"

void	free_list(t_node *list)
{
	int	i;

	if (list->next)
		free_list(list->next);
	if (list->fdin > 2)
		close(list->fdin);
	if (list->fdout > 2)
		close(list->fdout);
	i = 0;
	while (list->args[i])
	{
		free(list->args[i]);
		i++;
	}
	free(list->args);
}

t_node	*init_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->args = ft_calloc(1, sizeof(char *));
	if (node->args == NULL)
	{
		free(node);
		return (NULL);
	}
	node->fdin = 0;
	node->fdout = 1;
	node->next = NULL;
	return (node);
}

void	test_print_list(t_node *list)
{
	while (list)
	{
		printf("---------\n");
		printf("args:\n");
		for (int i = 0; list->args[i]; i++)
			printf(" - %s\n", list->args[i]);
		printf("fdin: %d - fdout: %d\n", list->fdin, list->fdout);
		list = list->next;
	}
	printf("---------\n");
}

int	parse_input(t_node *node, char *input)
{
	char	inside; // what kind of quotes are we inside?
	int		i;
	int		res;
	char	*arg;

	inside = 0; // at start, none
	i = 0;
	arg = ft_calloc(1, 1);
	while (input[i])
	{
		if (ft_strchr("\'\"", input[i]))
		{
			if (inside == 0) // quote starts
				inside = input[i];
			else if (inside == input[i]) // quote ends
				inside = 0;
		}
		else if (ft_strchr("<>", input[i]) && inside == 0) // redir symbol that is not inside any quotes
		{
			res = update_fd(node, &input[i]); // open file and set fd etc
			if (res == 0) // open failed (no filename, cant open...)
			{
				printf("redirection error\n");
				return (0);
			}
			i += res; // if success, increment i by redir symbols + filename length + any spaces between them
			continue ;
		}
		else if (input[i] == '$' && inside != '\'') // dollar sign that is not inside single quotes
		{
			res = expand(&arg, &input[i]); // append value of env var to arg
			if (res == 0)
			{
				printf("expand error\n");
				return (0);
			}
			if (res > 0) // arg now holds the expanded value
			{
				i += res; // increment i by the env vars key length
				continue ;
			}
		}
		else if (input[i] == ' ' && inside == 0) // space that is not inside any quotes, this arg ready.
		{
			if (*arg) // if arg contains something
				add(&node->args, arg); // add arg to args
			arg = ft_calloc(1, 1); // initialize new arg
			while (input[i] == ' ')
				i++;
			continue ;
		}
		else if (input[i] == '|' && inside == 0) // unquoted pipe, this node ready.
		{
			if (*arg) // if arg contains something
				add(&node->args, arg); // node is ready, add last arg
			node->next = init_node();
			if (node->next == NULL)
				return (0);
			node = node->next; // move to next node
			arg = ft_calloc(1, 1); // new arg
		}
		else
			append(&arg, input[i]); // add char to end of arg
		i++;
	}
	if (*arg)
		add(&node->args, arg); // input over, add last arg to args
	return (1);
}

int main(int argc, char **argv)
{
	t_node	*start;

	start = init_node();
	if (start == NULL)
		return (1);
	if (argc != 2)
	{
		printf("Give an input\n");
		return (1);
	}
	parse_input(start, argv[1]);
	test_print_list(start);
	free_list(start);
	return (0);
}

