/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:58:23 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/25 00:39:28 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_groups(t_group **groups);

t_shell	init_shell(char **env)
{
	t_shell	shell;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	shell.env = malloc(sizeof(char *) * (i + 1));
	if (!shell.env)
		return (shell);
	shell.env_vars = malloc(sizeof(t_env_var *));
	if (!shell.env_vars)
	{
		free(shell.env);
		return (shell);
	}
	*shell.env_vars = NULL;
	while (j < i)
	{
		shell.env[j] = ft_strdup(env[j]);
		if (!shell.env[j])
		{
			while (j > 0)
				free(shell.env[--j]);
			free(shell.env);
			return (shell);
		}
		j++;
	}
	shell.env[i] = NULL;
	return (shell);
}

void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
		free(shell->env[i++]);
	free_all_env_vars(shell->env_vars);
	free(shell->env);
	free(shell->pipe_groups);
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
		// free(line); // Results in a double free error
	}
	return (0);
}
