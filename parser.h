#ifndef PARSER_H
# define PARSER_H

#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef enum Rtype
{
	IN,
	OUT,
	APPEND,
	HEREDOC,
	NONE
}	rtype;

typedef struct s_node
{
	char			**args;
	int				fdin;
	int				fdout;
	struct s_node	*next;
}	t_node;

int	join(char **str, char *s);
int	update_fd(t_node *node, char *input);
int	append(char **str, char c);
int	arr_len(char **arr);
int	add(char ***arr, char *str);
int	expand(char **arg, char *str);

#endif
