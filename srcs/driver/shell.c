/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:58:23 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/25 01:49:55 by dkolida          ###   ########.fr       */
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
	free(shell->env);
}

int	run_shell(t_shell *shell)
{
	char	*line;
	char **tokens;

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
		shell->pipe_groups = group_input(line);
		tokens = tokenize(line);
		if (tokens != NULL)
		{
			while (*tokens)
			{
				printf("%s\n", *tokens);
				tokens++;
			}
		}
		//print_groups(shell->pipe_groups);
		free_groups(shell->pipe_groups);
	}
	return (0);
}
