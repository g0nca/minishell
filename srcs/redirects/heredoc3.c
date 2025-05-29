/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:33:19 by andrade           #+#    #+#             */
/*   Updated: 2025/05/29 15:07:40 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	error_create_heredoc(t_shell *shell)
{
	shell_error(shell, "Failed to create heredoc", 0, false);
	return (1);
}

int	process_heredoc(t_token *token, t_shell *shell)
{
	t_token	*current;
	t_token	*heredoc_token;
	t_token	*delimiter_token;
	char	*filename;

	current = token;
	while (current)
	{
		if (current->type == TOKEN_HERE_DOC && current->next)
		{
			heredoc_token = current;
			delimiter_token = current->next;
			filename = create_heredoc(delimiter_token->value, shell);
			if (!filename)
				error_create_heredoc(shell);
			free(heredoc_token->value);
			heredoc_token->value = ft_strdup(filename);
			free(filename);
			heredoc_token->type = TOKEN_REDIR_IN;
			remove_token(&token, delimiter_token);
			current = heredoc_token->next;
			continue ;
		}
		current = current->next;
	}
	return (0);
}
