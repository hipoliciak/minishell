/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_child_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 19:36:59 by dkolida           #+#    #+#             */
/*   Updated: 2024/09/01 20:59:18 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_child_proccess(t_shell *shell, int *pipe_fd, int in_fd, int i);

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
				O_WRONLY | O_CREAT | O_TRUNC, 0644), pipe_fd);
	else
	{
		if (i < shell->group_i)
			close(pipe_fd[0]);
		else
			close(in_fd);
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
