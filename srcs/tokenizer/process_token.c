/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:05:18 by ggomes-v          #+#    #+#             */
/*   Updated: 2025/10/24 14:04:29 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	process_token(t_token *list, char *line, int *i, t_shell *shell)
{
	if (line[*i] == '|')
	{
		add_token(list, "|", TOKEN_PIPE);
		(*i)++;
	}
	else if (line[*i] == '>' && line[*i + 1] == '>')
		process_append_token(list, i);
	else if (line[*i] == '<' && line[*i + 1] == '<')
		process_heredoc_token(list, i, shell);
	else if (line[*i] == '>')
		process_redir_out_token(list, i);
	else if (line[*i] == '<')
		process_redir_in_token(list, i);
	else
		tokenizer_word(list, i, line);
}

void	process_append_token(t_token *list, int *i)
{
	add_token(list, ">>", TOKEN_APPEND);
	*i += 2;
}

void	process_heredoc_token(t_token *list, int *i, t_shell *shell)
{
	shell->heredoc_counter++;
	add_token(list, "<<", TOKEN_HERE_DOC);
	*i += 2;
}

void	process_redir_out_token(t_token *list, int *i)
{
	add_token(list, ">", TOKEN_REDIR_OUT);
	(*i)++;
}

void	process_redir_in_token(t_token *list, int *i)
{
	add_token(list, "<", TOKEN_REDIR_IN);
	(*i)++;
}
