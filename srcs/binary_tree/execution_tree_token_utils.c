#include "../../inc/minishell.h"

static int should_skip_redirection(t_token *tmp)
{
    if (tmp->next && is_redirection(tmp->next->type))
        return (1);
    return (0);
}

int count_valid_tokens(t_token *start, t_token *end)
{
    int count;
    t_token *tmp;
    
    tmp = start;
    count = 0;
    while (tmp && tmp != end)
    {
        if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_CMD)
        {
            if (tmp->next && is_redirection(tmp->next->type))
            {
                tmp = tmp->next->next;
                continue;
            }
            count++;
        }
        tmp = tmp->next;
    }
    return (count);
}

void cleanup_argv_on_error(char **argv, int count)
{
    int j;

    j = 0;
    while (j < count)
    {
        free(argv[j]);
        j++;
    }
    free(argv);
}

void fill_argv_array(t_token *start, t_token *end, char **argv, int count)
{
    t_token *tmp;
    int i;

    i = 0;
    tmp = start;
    while (tmp && tmp != end && i < count)
    {
        if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_CMD)
        {
            if (should_skip_redirection(tmp))
            {
                tmp = tmp->next->next;
                continue;
            }
            argv[i] = strdup(tmp->value);
            if (!argv[i])
            {
                cleanup_argv_on_error(argv, i);
                return ;
            }
            i++;
        }
        tmp = tmp->next;
    }
    argv[i] = NULL;
}