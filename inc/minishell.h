/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:14:44 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/04/03 10:38:28 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
//# include "ft_printf.h"
#include <ctype.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>

/*typedef enum e_token_type {
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC
}   t_token_type;

typedef struct s_token {
    char            *value;
    t_token_type    type;
    struct s_token  *next;
}   t_token;*/

typedef struct s_shell
{
    char **env;
    int last_exit_status;
    int running;
}   t_shell;


int     main(int ac, char **av, char **envp);
char    **copy_env(char **envp);

//  free_functions
void free_env(char **env);


//      LIBFT
int	ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s);



#endif