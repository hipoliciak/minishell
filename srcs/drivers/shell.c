/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:58:23 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/09/02 00:07:44 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env_vars = malloc(sizeof(t_env_var *));
	if (!shell->env_vars)
	{
		free(shell);
		return (NULL);
	}
	*shell->env_vars = NULL;
	shell->last_exit_code = 0;
	set_shell_env_vars(shell, env);
	shell->env = env_vars_to_env(shell->env_vars);
	return (shell);
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env)
		ft_free_split(shell->env);
	if (shell->env_vars)
	{
		free_all_env_vars(shell->env_vars);
		free(shell->env_vars);
	}
	free(shell);
}

int	run_shell(t_shell *shell)
{
	char	*line;

	line = NULL;
	while (1)
	{
		set_signals_interactive();
		line = ft_read_line(line);
		if (!line)
		{
			printf("Exiting minishell.\n");
			rl_clear_history();
			break ;
		}
		if (*line != '\0')
		{
			set_signals_for_execution();
			shell_exec(shell, get_tokens(shell, line));
			set_signals_interactive();
		}
	}
	return (0);
}
