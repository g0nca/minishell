/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:29:58 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/05/22 12:52:58 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void    handle_double_dollar(const char **input, char **current)
{
    char    *pid_str;
    int     pid;
    int     i;

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
}
static void    handle_question_mark(const char **input, char ** current)
{
    char    *status_str;
    int     i;

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
}
// Função auxiliar que extrai o nome da variável e atualiza o ponteiro input
static char *extract_variable_name(const char **input)
{
	char	*var;
	int		var_len;
	int		i;
	const char *tmp;

    tmp = *input;
    var_len = 0;
    i = 0;
	while (ft_isalnum(tmp[var_len]) || tmp[var_len] == '_')
		var_len++; //count the variable length
	var = (char *)malloc(sizeof(char) * (var_len + 1));
	if (!var)
		return (NULL);
	while (i < var_len) // copy the variable name
		var[i++] = *(*input)++;
	var[i] = '\0';
	return (var);
}

static void handle_env_variable_expansion(const char **input, char **current, char **envp)
{
	char	*var;
	char	*value;
	int		i;

	var = extract_variable_name(input);
	if (!var)
		return;
	value = get_env_value(var, envp);
	free(var);
	if (value)
	{
		i = 0;
		while (value[i])
			*(*current)++ = value[i++];
	}
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
     (*input)++; // avança para o próximo caractere
     if (**input == '$') // caso $$ → PID
     {
         handle_double_dollar(input, current);
         return ;
     }
     if (**input == '?') // caso $? → exit status
     {
         handle_question_mark(input, current);
         return ;
     }
     if (ft_isalpha(**input) || **input == '_')  // Case $VARIABLE
     {
         handle_env_variable_expansion(input, current, envp);
         return ;
     }
     *(*current)++ = '$'; // If not recognized ($$ $?) → write only '$'
}