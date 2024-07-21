/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:58:23 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/21 15:37:31 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void sigint_handler(int sig_num);

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

int	run_shell(t_shell *shell)
{
	(void)shell;
	char *line;
	signal(SIGINT, sigint_handler);
	while (1)
	{

		line = readline("minishell$ ");
		if (!line)
		{
			printf("\nExiting minishell.\n");
			break ;
		}
		printf("%s\n", line);
		free(line);
	}
	return (0);
}

void sigint_handler(int sig_num)
{
	(void)sig_num;
	signal(SIGINT, sigint_handler);
	ft_putendl_fd("", 1);
	// Prepare readline for the next input
	rl_on_new_line(); // Tell readline that we've moved to a new (empty) line
	rl_replace_line("", 0); // Clear the current line
	rl_redisplay(); // Redisplay the prompt on a new line
}
