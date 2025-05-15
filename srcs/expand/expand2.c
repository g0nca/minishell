/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:29:58 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/06 14:57:57 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/**
 * @brief Retrieves the value of a specified environment variable.
 *
 * Searches the envp array for a variable matching the given name and
 * returns a pointer to the corresponding value (i.e., the part after '=').
 *
 * For example, if name = "PATH" and envp[i] = "PATH=/usr/bin",
 * the function returns a pointer to "/usr/bin".
 *
 * @param name The name of the environment variable to search for (e.g., "HOME").
 * @param envp Array of environment variables in the format "VAR=value".
 * @return A pointer to the value part of the environment variable, or NULL if not found.
 */

char *get_env_value(const char *name, char **envp)
{
    int len;
	int i;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
    while (envp[i]) 
	{
        if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
            return (envp[i] + len + 1);
		i++;
    }
    return (NULL);
}
/**
 * @brief Expands environment variables found in a given input string.
 *
 * This function scans the input string for environment variable patterns
 * prefixed with '$' (e.g., $HOME, $PATH). When a variable is detected, it
 * retrieves its value from the environment (envp) and appends it to the result.
 *
 * Non-variable characters are copied directly to the result string.
				** Percorre a string de input e copia caractere por caractere para a string de saída.
				** Quando encontra um '$' seguido de uma variável (ex: $USER), substitui pelo valor correspondente.
				** Utiliza um ponteiro auxiliar 'current' para escrever na memória alocada,
				** enquanto 'result' permanece apontando para o início da string resultante.
				** No final, retorna 'result', que contém o input expandido com as variáveis de ambiente.
 * @param input The input string that may contain environment variables.
 * @param envp The array of environment variables in the form "VAR=value".
 * @param list Unused in this function (reserved for future use or context).
 * @return A newly allocated string with the expanded variables. Must be freed by the caller.
 */

char *expand_variables(const char *input, char **envp, t_token *list)
{
    char    *result;
    char    *current;
    size_t  size;
    int     in_single_quote;

    (void)list;
    size = calculate_final_size(input, envp);
    result = (char *)malloc(size + 1);
    if (!result)
        return (NULL);
    current = result;
    in_single_quote = 0;

    while (*input)
    {
        if (*input == '\'')
        {
            in_single_quote = !in_single_quote;   // alterna flag
            *current++ = *input++;
        }
        else if (*input == '$' && !in_single_quote)
        {
            copy_env_value(&input, &current, envp);
        }
        else
        {
            *current++ = *input++;
        }
    }
    *current = '\0';
    return (result);
}

 /**
  * @brief Copies the value of an environment variable to the result buffer.
  *
  * This function parses the variable name starting from the given input pointer,
  * retrieves its value from the environment, and writes it to the `current` result pointer.
  *
  * @param input Pointer to the input string containing the variable name (e.g., "$USER").
  *              The pointer is advanced past the variable after processing.
  * @param current Pointer to the result buffer where the variable's value will be written.
  *                The pointer is advanced after writing the value.
  * @param envp Array of environment variables in the format "VAR=value".
  */
void	copy_env_value(const char **input, char **current, char **envp)
{
	char	*var;
	char	*value;
    int		i;
 
	(*input)++; // avança para o próximo caractere
 
	if (**input == '$') // caso $$ → PID
	{
		char *pid_str;
		int pid;

        pid = getpid();
		pid_str = ft_itoa(pid);
		if (pid_str)
		{
			i = 0;
			while (pid_str[i])
			{
				*(*current)++ = pid_str[i];
				i++;
			}
			free(pid_str);
		}
		(*input)++; // consome o segundo '$'
		return ;
	 }
 
	if (**input == '?') // caso $? → exit status
	{
		char *status_str;
		status_str = ft_itoa(g_exit_status);

		if (status_str)
		{
			i = 0;
			while (status_str[i])
			{
				*(*current)++ = status_str[i];
				i++;
			}
			free(status_str);
		}
		(*input)++;
		return ;
	}
    if (ft_isalpha(**input) || **input == '_')  // Case $VARIABLE
    {
        int var_len;
        const char *tmp;
		
		var_len = 0;
		tmp = *input;
        while (ft_isalnum(tmp[var_len]) || tmp[var_len] == '_')
            var_len++; // Count the variable name length first
        var = (char *)malloc(sizeof(char) * (var_len + 1));
        if (!var)
            return;
        i = 0; // Extract the variable name
        while (i < var_len)
        {
            var[i] = **input;
            (*input)++;
            i++;
        }
        var[i] = '\0';
        value = get_env_value(var, envp);
        free(var);
        if (value)
        {
            i = 0;
            while (value[i])
            {
                *(*current)++ = value[i];
                i++;
            }
        }
        return ;
    }
    *(*current)++ = '$'; // If not recognized ($$ $?) → write only '$'
}

 /**
  * @brief Calculates the total length of the input string after variable expansion.
  *
  * This function determines how much memory needs to be allocated by computing
  * the final size of the string after expanding all valid environment variables.
  *
  * @param input The input string possibly containing variables (e.g., "$PATH").
  * @param envp Array of environment variables in the format "VAR=value".
  * @return The total length required for the expanded string (excluding null-terminator),
  *         or (size_t)-1 if input or envp is NULL.
  */
 
size_t calculate_final_size(const char *input, char **envp)
{
    size_t size;
    size_t var_len;
    char *var;
    char *value;
    int in_single_quote;

    size = 0;
    in_single_quote = 0;
    while (*input)
    {
        if (*input == '\'')
        {
            in_single_quote = !in_single_quote;
            size++;     // conta a aspa no resultado
            input++;
        }
        else if (*input == '$' && !in_single_quote)
        {
            input++; // Skip '$'
            if (*input == '$') // Handle $$
            {
                size += 10; // espaço suficiente para PID
                input++;
            }
            else if (*input == '?') // Handle $?
            {
                size += 5; // espaço suficiente para status
                input++;
            }
            else if (ft_isalpha(*input) || *input == '_') // Handle $VAR
            {
                const char *start; 
                
                start = input;
                var_len = 0;
                while (ft_isalnum(*input) || *input == '_')
                {
                    var_len++;
                    input++;
                }
                var = (char *)malloc(sizeof(char) * (var_len + 1));
                if (!var)
                    return size;
                ft_strncpy(var, start, var_len);
                var[var_len] = '\0';
                value = get_env_value(var, envp);
                free(var);
                if (value)
                    size += ft_strlen(value);
            }
            else
            {
                // caso especial: "$" sozinho ou com caractere inválido
                size++; // para o próprio '$'
            }
        }
        else
        {
            size++;
            input++;
        }
    }
    return (size);
}


 /**
  * @brief Parses and processes a single environment variable to update the size counter.
  *
  * This function extracts the variable name starting from the input, retrieves
  * its value from the environment, and adds the value's length to the total size.
  *
  * @param input Pointer to the input string containing the variable. It is advanced after processing.
  * @param size Pointer to the size accumulator to be incremented by the variable value length.
  * @param envp Array of environment variables in the format "VAR=value".
  */
void	process_env_var(const char **input, size_t *size, char **envp)
{
	 char	*var;
	 char	*value;
	 int		i;
 
	 var = (char *)malloc(sizeof(char *) * (ft_strlen(*input)) + 1);
	 if (!var)
		 return ;
	 (*input)++;
	 i = 0;
	 while (ft_isalnum(**input) || **input == '_')
		 var[i++] = *(*input)++;
	 var[i] = '\0';
	 value = get_env_value(var, envp);
	 free(var);
	 if (value)
		 *size += ft_strlen(value);
}
