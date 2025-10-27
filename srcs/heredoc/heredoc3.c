/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 10:33:19 by andrade           #+#    #+#             */
/*   Updated: 2025/10/27 12:01:31 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	error_create_heredoc(t_shell *shell)
{
	shell_error(shell, "Failed to create heredoc", 0, false);
	return (1);
}

static void	update_heredoc_token(t_token *heredoc_token, char *filename)
{
	free(heredoc_token->value);
	heredoc_token->value = ft_strdup(filename);
	heredoc_token->type = TOKEN_REDIR_IN;
}

static int	handle_heredoc2(t_token *current, t_token **token, t_shell *shell)
{
	t_token	*heredoc_token;
	t_token	*delimiter_token;
	char	*filename;

	heredoc_token = current;
	delimiter_token = current->next;
	filename = create_heredoc(delimiter_token->value, shell);
	if (!filename)
		return (error_create_heredoc(shell));
	update_heredoc_token(heredoc_token, filename);
	free(filename);
	remove_token(token, delimiter_token);
	return (0);
}

int	process_heredoc(t_token *token, t_shell *shell)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type == TOKEN_HERE_DOC && current->next)
		{
			if (handle_heredoc2(current, &token, shell) != 0)
				return (1);
			current = current->next;
			continue ;
		}
		current = current->next;
	}
	return (0);
}

void	handle_heredoc(t_token *token, t_shell *shell)
{
	if (process_heredoc(token, shell) != 0)
		shell->last_exit_status = 1;
}
