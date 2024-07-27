/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:58:23 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/28 01:26:34 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_groups(t_group **groups);
void	print_tokens(char **tokens);

t_shell	*init_shell(void)
{
	t_shell	*shell;
	char	*cwd;

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
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		set_env_var(shell, "PWD", cwd);
		free(cwd);
	}
	set_env_var(shell, "HOME", getenv("HOME"));
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
	free(shell);
}

int	run_shell(t_shell *shell)
{
	char		*line;
	t_tokenizer	*tokenizer_data;

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
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		tokenizer_data = tokenizer_create(line);
		if (tokenizer_data)
		{
			exec_builtins(shell, tokenizer_data->tokens);
			free_tokenizer(tokenizer_data);
		}
	}
	return (0);
}

void	print_tokens(char **tokens)
{
	while (*tokens)
	{
		printf("%s\n", *tokens);
		tokens++;
	}
}
