
#include "../../inc/minishell.h"

char **tokens_to_argv(t_token *start, t_token *end)
{
    int count;
    char **argv;

    count = count_valid_tokens(start, end);
    argv = malloc(sizeof(char *) * (count + 1));
    if (!argv)
        return (NULL);
        
    fill_argv_array(start, end, argv, count);
    return (argv);
}