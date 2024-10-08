/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 22:35:37 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/09/05 22:21:44 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envp_path(char **envp)
{
	int		i;
	char	**path;
	char	*temp;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			temp = ft_strdup(envp[i] + 5);
			if (!temp)
				return (NULL);
			path = ft_split(temp, ':');
			free(temp);
			if (!path)
				return (NULL);
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(char **path, char *cmd)
{
	int		i;
	char	*full_path;
	char	*temp;

	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	is_absolute_or_relative_path(char *cmd)
{
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (1);
	}
	return (0);
}

char	*set_path(t_shell *shell, char **args)
{
	char	**path;
	char	*full_path;

	if (is_absolute_or_relative_path(args[0]) != 0)
		return (ft_strdup(args[0]));
	path = envp_path(shell->env);
	if (!path)
	{
		ft_putendl_fd(" command not found", 2);
		shell->last_exit_code = 127;
		return (NULL);
	}
	full_path = get_path(path, args[0]);
	if (!full_path)
	{
		ft_putendl_fd(" command not found", 2);
		shell->last_exit_code = 127;
		ft_free_split(path);
		return (NULL);
	}
	ft_free_split(path);
	return (full_path);
}

int	execve_path(t_shell *shell, char **args)
{
	char	*full_path;
	int		status;

	full_path = set_path(shell, args);
	if (!full_path)
		return (1);
	status = execve(full_path, args, shell->env);
	if (status == -1)
		status = 126;
	perror("execve");
	free(full_path);
	exit(status);
	return (status);
}
