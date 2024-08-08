/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:58:23 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/07 16:31:39 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_exec(t_shell *shell, char *line);

t_shell	*init_shell(void)
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
	set_shell_env_vars(shell);
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

	signal(SIGINT, sigint_handler);
	line = NULL;
	while (1)
	{
		line = ft_read_line(line);
		if (!line)
		{
			printf("Exiting minishell.\n");
			rl_clear_history();
			break ;
		}
		if (*line != '\0')
			shell_exec(shell, line);
	}
	return (0);
}

void	shell_exec(t_shell *shell, char *line)
{
	char	**tokens;
	int		i;

	i = 0;
	tokens = get_tokens(shell, line);
	if (tokens)
	{
		group_input(shell, tokens);
		i = 0;
		while (shell->groups[i])
		{
			exec_command(shell, shell->groups[i]->args);
			i++;
		}
		ft_free_split(tokens);
		free_groups(shell->groups);
	}
}
