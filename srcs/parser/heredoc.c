/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:26:28 by dkolida           #+#    #+#             */
/*   Updated: 2024/09/14 19:09:13 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_heredoc_handler(char *template, char *delimiter);

void	heredoc(t_shell *shell, t_tokenizer *data, int *grp_i, int *i)
{
	char	*delimiter;
	char	*template;
	int		pid;

	delimiter = data->tokens[++(*i)];
	template = NULL;
	template = ft_strdup("minishell_heredoc");
	pid = fork();
	if (pid == 0)
		child_heredoc_handler(template, delimiter);
	else
	{
		wait(NULL);
		shell->groups[*grp_i]->in_file_name = strdup(template);
	}
	free(template);
}

void	child_heredoc_handler(char *template, char *delimiter)
{
	char	*line;
	int		temp_fd;

	temp_fd = open(template, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (temp_fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	line = readline("heredoc> ");
	while (line != NULL)
	{
		if (strncmp(line, delimiter, strlen(delimiter)) == 0
			&& line[strlen(delimiter)] == '\0')
		{
			free(line);
			break ;
		}
		write(temp_fd, line, strlen(line));
		write(temp_fd, "\n", 1);
		free(line);
		line = readline("heredoc> ");
	}
	close(temp_fd);
	exit(EXIT_SUCCESS);
}
