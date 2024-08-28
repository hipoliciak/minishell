/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:41:17 by dkolida           #+#    #+#             */
/*   Updated: 2024/08/28 18:29:57 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_shell *shell, int *pipefd)
{
	int	in_fd;

	if (shell->groups[0]->in_file_name)
	{
		in_fd = open(shell->groups[0]->in_file_name, O_RDONLY);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	pipe_exec(shell);
	perror("pipe_exec");
	exit(EXIT_FAILURE);
}

void	parent_process(int *pipefd, int pid)
{
	char	*line;

	close(pipefd[1]);
	line = get_next_line(pipefd[0]);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(pipefd[0]);
	}
	free(line);
	close(pipefd[0]);
	waitpid(pid, NULL, 0);
}
