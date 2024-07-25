/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:58:23 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/26 00:11:30 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_groups(t_group **groups);

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
	shell->pipe_groups = NULL;
	set_env_var(shell, "HOME", getenv("HOME"));
	set_env_var(shell, "PWD", getcwd(NULL, 0));
	set_env_var(shell, "USER", getenv("USER"));
	return (shell);
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env_vars)
	{
		free_all_env_vars(shell->env_vars);
		free(shell->env_vars);
	}
	if (shell->pipe_groups)
		free_groups(shell->pipe_groups);
}

int	run_shell(t_shell *shell)
{
	char	*line;

	(void)shell;
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
		if (ft_strchr(line, '|'))
		{
			shell->pipe_groups = group_input(line);
			print_groups(shell->pipe_groups);
			free_groups(shell->pipe_groups);
		}
		else
			parse_command(shell, line);
	}
	return (0);
}
