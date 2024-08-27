/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:58:23 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/27 14:54:43 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_exec(t_shell *shell, char **tokens);
void	pipe_exec(t_shell *shell);

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
	char	**tokens;

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
		{
			tokens = get_tokens(shell, line);
			shell_exec(shell, tokens);
		}
	}
	return (0);
}

void	shell_exec(t_shell *shell, char **tokens)
{
	int		pid;
	int		pipefd[2];

	if (tokens)
	{
		group_input(shell, tokens);
		make_pipe(pipefd);
		pid = make_fork();
		if (pid == 0)
			child_process(shell, pipefd);
		else
			parent_process(pipefd, pid);
		ft_free_split(tokens);
	}
	free_groups(shell->groups);
}

void	pipe_exec(t_shell *shell)
{
	int	pipefd[2];
	int	pid;

	if (shell->group_i > 0)
	{
		make_pipe(pipefd);
		pid = make_fork();
		if (pid == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			shell->group_i--;
			pipe_exec(shell);
		}
		else
		{
			close(pipefd[1]);
			waitpid(pid, NULL, 0);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
	}
	execve_path(shell, shell->groups[shell->group_i]->args);
}
// To replace last line when buildins will be implemented with exit()
//exec_command(shell, shell->groups[shell->group_i]->args);
