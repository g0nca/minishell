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
