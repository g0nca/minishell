/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggomes-v <ggomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:36:30 by andrade           #+#    #+#             */
/*   Updated: 2025/10/21 15:17:11 by ggomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error_heredoc(const char *delimiter)
{
	ft_printf_fd(2, "minishell: warning: ");
	ft_printf_fd(2, "here-document delimited ");
	ft_printf_fd(2, "by end-of-file (wanted `%s')\n", delimiter);
}

char	*generate_temp_filename(int i)
{
	char	*num_str;
	char	*filename;

	num_str = ft_itoa(i);
	if (!num_str)
		return (NULL);
	filename = ft_strjoin("/tmp/minishell_heredoc_", num_str);
	free(num_str);
	return (filename);
}

int	create_temp_file(char **out_filename)
{
	char	*filename;
	int		fd;
	int		i;

	i = 0;
	while (1)
	{
		filename = generate_temp_filename(i);
		if (!filename)
			return (-1);
		fd = open(filename, O_WRONLY | O_CREAT | O_EXCL, 0600);
		if (fd >= 0)
		{
			*out_filename = filename;
			return (fd);
		}
		free(filename);
		i++;
	}
}

void	remove_token(t_token **head, t_token *to_remove)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	curr = *head;
	while (curr)
	{
		if (curr == to_remove)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	cleanup_heredoc_files(t_shell *shell)
{
	t_list	*temp;
	t_list	*next;

	if (!shell || !shell->heredoc_files)
		return ;
	temp = shell->heredoc_files;
	while (temp)
	{
		next = temp->next;
		if (temp->content && temp->content != NULL)
		{
			unlink((char *)temp->content);
			free(temp->content);
		}
		free(temp);
		temp = next;
	}
	shell->heredoc_files = NULL;
}
