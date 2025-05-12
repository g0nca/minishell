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

char	*expand_variables(const char *input, char **envp, t_token *list)
{
	char	*result;
	char	*current;
	(void)list;
	result = (char *)malloc(calculate_final_size(input, envp) + 1);
	if (!result)
		return (NULL);
	current = result;
	while (*input)
	{
		if (*input == '$')
			 copy_env_value(&input, &current, envp);
		else
		{
			*current = *input;
			current++;
			input++;
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
 
	 // estamos garantidos que *input[0] == '$'
	 (*input)++; // avança para o próximo caractere
 
	 if (**input == '$') // caso $$ → PID
	 {
		 char pid_str[20];
		 int pid = getpid();
		 sprintf(pid_str, "%d", pid);
 
		 // Substituindo o for por while
		 i = 0;
		 while (pid_str[i])
		 {
			 *(*current)++ = pid_str[i];
			 i++;
		 }
		 (*input)++; // consome o segundo '$'
		 return ;
	 }
 
	 if (**input == '?') // caso $? → exit status
	 {
		 char status_str[12];
		 sprintf(status_str, "%d", g_exit_status);
 
		 // Substituindo o for por while
		 i = 0;
		 while (status_str[i])
		 {
			 *(*current)++ = status_str[i];
			 i++;
		 }
		 (*input)++;
		 return ;
	 }
 
	 // caso $VARIAVEL
	 if (ft_isalpha(**input) || **input == '_')
	 {
		 var = (char *)malloc(sizeof(char) * (ft_strlen(*input) + 1));
		 if (!var)
			 return ;
		 i = 0;
		 while (ft_isalnum(**input) || **input == '_')
		 {
			 var[i++] = *(*input)++;
		 }
		 var[i] = '\0';
 
		 value = get_env_value(var, envp);
		 free(var);
		 if (value)
		 {
			 // Substituindo o for por while
			 i = 0;
			 while (value[i])
			 {
				 *(*current)++ = value[i];
				 i++;
			 }
		 }
		 return ;
	 }
 
	 // se não for nada reconhecido ($$ $?) → escreve só '$'
	 *(*current)++ = '$';
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
 
size_t	calculate_final_size(const char *input, char **envp)
{
	 size_t	size;
 
	 size = 0;
	 if (!input || !envp)
		 return (-1);
	 while (*input)
	 {
		 if (*input == '$' && ft_isalpha(*(input + 1)))
			 process_env_var(&input, &size, envp);
		 else
		 {
			 size += 1;
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
