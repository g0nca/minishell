
#include "../../inc/minishell.h"

size_t calculate_final_size(const char *input, char **envp)
{
    size_t size;
    int in_single_quote;
    size_t added;

    in_single_quote = 0;
    size = 0;
    while (*input)
    {
        if (*input == '\'')
        {
            in_single_quote = !in_single_quote;
            size++;
            input++;
        }
        else
        {
            added = handle_dollar(&input, envp, in_single_quote);
            if (added > 0)
                size += added;
            else
            {
                size++;
                input++;
            }
        }
    }
    return (size);
}
size_t handle_dollar(const char **input, char **envp, int in_single_quote)
{
    size_t size;

    size = 0;
    if (**input == '$' && !in_single_quote)
    {
        if (**input == '$')
        {
            size += 10;
            (*input)++;
        }
        else if (**input == '?')
        {
            size += 5;
            (*input)++;
        }
        else if (ft_isalpha(**input) || **input == '_')
            size += handle_env_variable(input, envp);
        else
            size += 1;
    }
    return (size);
}

size_t handle_env_variable(const char **input, char **envp)
{
    const char  *start;
    size_t      var_len;
    char        *var;
    char        *value;
    size_t      size;

    var_len = 0;
    size = 0;
    start = *input;
    while (**input && (ft_isalnum(**input) || **input == '_'))
    {
        var_len++;
        (*input)++;
    }
    var = (char *)malloc(sizeof(char) * (var_len + 1));
    if (!var)
        return (0);
    ft_strncpy(var, start, var_len);
    var[var_len] = '\0';
    value = get_env_value(var, envp);
    if (value)
        size = ft_strlen(value);
    free(var);
    return (size);
}
