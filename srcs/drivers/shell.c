/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:58:23 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/30 03:25:22 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_exec(t_shell *shell, char **tokens);
void	pipe_exec(t_shell *shell);

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
	char	**tokens;

	line = NULL;
	while (1)
	{
		set_signals_interactive();
		set_signals_noninteractive();
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

void shell_exec(t_shell *shell, char **tokens)
{
	int i = 0;
	int in_fd = -1;
	int pipe_fd[2];
	char buffer[65536];
	ssize_t bytes_read;
	int terminal_fd;
	int	pid;

	if (tokens)
	{
		group_input(shell, tokens);
		terminal_fd = dup(STDOUT_FILENO);
		if (terminal_fd == -1) {
			perror("dup");
			exit(EXIT_FAILURE);
		}

		while (i <= shell->group_i)
		{

			make_pipe(pipe_fd);
			if (is_builtin(shell->groups[i]->args[0]))
			{
				shell->out_fd = pipe_fd[1];
				exec_builtin(shell, shell->groups[i]->args);
				close(pipe_fd[1]);
				in_fd = dup(pipe_fd[0]);
				if (i < shell->group_i)
					close(pipe_fd[0]);
				else
					close(in_fd);
			}
			else
			{
				pid = make_fork();
				if (pid == 0)
				{
					if (in_fd > 0)
					{
						dup2(in_fd, STDIN_FILENO);
						close(in_fd);
					}
					close(pipe_fd[0]);
					dup2(pipe_fd[1], STDOUT_FILENO);
					close(pipe_fd[1]);
					exec_command(shell, shell->groups[i]->args);
					exit(shell->last_exit_code);
				}
				else
				{
					close(pipe_fd[1]);
					//waitpid(pid, NULL, 0);
					in_fd = dup(pipe_fd[0]);
					if (i < shell->group_i)
						close(pipe_fd[0]);
					else
						close(in_fd);
				}
			}
			i++;
		}
		while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1)) > 0)
		{
			buffer[bytes_read] = '\0';
			write(terminal_fd, buffer, bytes_read);
		}
		if (bytes_read == -1) {
			perror("read");
		}
		close(terminal_fd);
		close(pipe_fd[0]);
		ft_free_split(tokens);
	}
	free_groups(shell->groups, shell->tokens_count);
}
