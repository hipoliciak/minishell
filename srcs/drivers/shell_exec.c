/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:24:00 by dkolida           #+#    #+#             */
/*   Updated: 2024/08/30 21:40:01 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		shell_exec_group(t_shell *shell, int *pipe_fd, int in_fd, int i);
int		shell_exec_buildin(t_shell *shell, int *pipe_fd, int in_fd, int i);
int		shell_exec_in_child(t_shell *shell, int *pipe_fd, int in_fd, int i);
void	shell_print_output(int terminal_fd, int *pipe_fd);

void	shell_exec(t_shell *shell, char **tokens)
{
	int		i;
	int		in_fd;
	int		pipe_fd[2];
	int		terminal_fd;

	if (tokens)
	{
		group_input(shell, tokens);
		terminal_fd = dup(STDOUT_FILENO);
		if (terminal_fd == -1)
		{
			perror("dup");
			exit(EXIT_FAILURE);
		}
		i = 0;
		in_fd = -1;
		while (i <= shell->group_i)
		{
			make_pipe(pipe_fd);
			in_fd = shell_exec_group(shell, pipe_fd, in_fd, i++);
		}
		shell_print_output(terminal_fd, pipe_fd);
		ft_free_split(tokens);
	}
	free_groups(shell->groups, shell->tokens_count);
}

int	shell_exec_group(t_shell *shell, int *pipe_fd, int in_fd, int i)
{
	if (shell->groups[i]->in_file_name)
	{
		if (in_fd > 0)
			close(in_fd);
		in_fd = open(shell->groups[i]->in_file_name, O_RDONLY);
	}
	if (shell->groups[i]->args[0] == NULL)
		return (in_fd);
	if (is_builtin(shell->groups[i]->args[0]))
		in_fd = shell_exec_buildin(shell, pipe_fd, in_fd, i);
	else
		in_fd = shell_exec_in_child(shell, pipe_fd, in_fd, i);
	return (in_fd);
}

int	shell_exec_buildin(t_shell *shell, int *pipe_fd, int in_fd, int i)
{
	if (shell->groups[i]->out_file_name)
	{
		shell->out_fd = open(shell->groups[i]->out_file_name,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else
		shell->out_fd = pipe_fd[1];
	exec_builtin(shell, shell->groups[i]->args);
	close(pipe_fd[1]);
	in_fd = dup(pipe_fd[0]);
	if (i < shell->group_i)
		close(pipe_fd[0]);
	else
		close(in_fd);
	return (in_fd);
}

int	shell_exec_in_child(t_shell *shell, int *pipe_fd, int in_fd, int i)
{
	int	pid;

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
	close(pipe_fd[1]);
	in_fd = dup(pipe_fd[0]);
	if (i < shell->group_i)
		close(pipe_fd[0]);
	else
		close(in_fd);
	return (in_fd);
}

void	shell_print_output(int terminal_fd, int *pipe_fd)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;

	bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		write(terminal_fd, buffer, bytes_read);
		bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE - 1);
	}
	if (bytes_read == -1)
		perror("read");
	close(terminal_fd);
	close(pipe_fd[0]);
}
