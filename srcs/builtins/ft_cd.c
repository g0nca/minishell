/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomart <joaomart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:05:57 by joaomart          #+#    #+#             */
/*   Updated: 2025/04/14 19:34:43 by joaomart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* void	cd_home(char *cmdargs, t_shell *shell)
{
	char	*home;

	home = getenv("HOME");
	chdir(home);
} */

void	ft_cd(t_token *cmdargs, t_shell *shell)
{
	t_token	*current;
	char	*cur_dir;
	//char	*old_pwd;

	current = cmdargs->next;
	cur_dir = getcwd(NULL, 0);
	if (!current || !ft_strcmp(current->value, "--")
		|| !ft_strcmp(current->value, "~"))
	{
		cur_dir = getenv("HOME");
		chdir(cur_dir);
	}
	else
	{
		
	}
	shell->last_exit_status = EXIT_SUCCESS;
}
