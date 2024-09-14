/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:24:00 by dkolida           #+#    #+#             */
/*   Updated: 2024/09/14 15:54:51 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		shell_exec_group(t_shell *shell, int *pipe_fd, int in_fd, int i);
int		shell_exec_buildin(t_shell *shell, int *pipe_fd, int in_fd, int i);
int		shell_exec_in_child(t_shell *shell, int *pipe_fd, int in_fd, int i);
void	shell_exec_loop(t_shell *shell);

void	shell_exec(t_shell *shell, t_tokenizer *tokens)
{
	if (tokens)
	{
		if (group_input(shell, tokens))
			shell_exec_loop(shell);
		else
		{
			shell->last_exit_code = 127;
			ft_putendl_fd("syntax error near unexpected token '\\n'", 2);
		}
		free_tokenizer(tokens);
		free_groups(shell->groups, shell->tokens_count);
	}
}

int	shell_exec_group(t_shell *shell, int *pipe_fd, int in_fd, int i)
{
	if (shell->groups[i]->in_file_name)
	{
		if (in_fd > 0)
			close(in_fd);
		in_fd = open(shell->groups[i]->in_file_name, O_RDONLY);
		if (in_fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
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
				output_mode(shell->groups[i]->out_file_append), 0644);
		if (shell->out_fd == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
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

void	shell_print_output(int fd, int *pipe_fd)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;

	if (fd == -1)
	{
		perror("file descriptor error");
		exit(EXIT_FAILURE);
	}
	bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE - 1);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		write(fd, buffer, bytes_read);
		bytes_read = read(pipe_fd[0], buffer, BUFFER_SIZE - 1);
	}
	if (bytes_read != -1)
	{
		if (errno == EINTR)
			shell_print_output(fd, pipe_fd);
		else
			close(pipe_fd[0]);
	}
}

void	shell_exec_loop(t_shell *shell)
{
	int	terminal_fd;
	int	pipe_fd[2];
	int	i;
	int	in_fd;

	terminal_fd = dup(STDOUT_FILENO);
	if (terminal_fd == -1)
		perror("duplicate terminal_fd failed");
	i = 0;
	in_fd = -1;
	while (i <= shell->group_i)
	{
		make_pipe(pipe_fd);
		in_fd = shell_exec_group(shell, pipe_fd, in_fd, i++);
	}
	shell_print_output(terminal_fd, pipe_fd);
	close(terminal_fd);
}
