/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_child_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:36:59 by dkolida           #+#    #+#             */
/*   Updated: 2024/09/06 16:17:26 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_child_proccess(t_shell *shell, int *pipe_fd, int in_fd, int i);
void	update_exit_code(t_shell *shell, int pid);

int	shell_exec_in_child(t_shell *shell, int *pipe_fd, int in_fd, int i)
{
	int	pid;

	pid = make_fork();
	if (pid == 0)
	{
		reset_signals();
		shell_child_proccess(shell, pipe_fd, in_fd, i);
	}
	close(pipe_fd[1]);
	in_fd = dup(pipe_fd[0]);
	if (shell->groups[i]->out_file_name)
		shell_print_output(open(shell->groups[i]->out_file_name,
				output_mode(shell->groups[i]->out_file_append), 0644), pipe_fd);
	else
	{
		if (i < shell->group_i)
			close(pipe_fd[0]);
		else
		{
			close(in_fd);
			update_exit_code(shell, pid);
		}
	}
	return (in_fd);
}

void	shell_child_proccess(t_shell *shell, int *pipe_fd, int in_fd, int i)
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
}

void	update_exit_code(t_shell *shell, int pid)
{
	int	status;
	int	signal_number;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signal_number = WTERMSIG(status);
		if (signal_number == SIGINT)
			shell->last_exit_code = 130;
		else
			shell->last_exit_code = 128 + signal_number;
	}
}
