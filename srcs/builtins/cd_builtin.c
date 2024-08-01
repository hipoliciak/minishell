/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:02:48 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/31 23:32:09 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	arg_error(t_shell *shell)
{
	ft_putendl_fd(" too many arguments", 2);
	shell->last_exit_code = 1;
	return (1);
}

static int	path_error(t_shell *shell, char *path)
{
	perror(path);
	if (path)
		free(path);
	shell->last_exit_code = 1;
	return (1);
}

static int	home_error(t_shell *shell)
{
	ft_putendl_fd("cd: HOME not set", 2);
	shell->last_exit_code = 1;
	return (1);
}

int	cd_builtin(t_shell *shell, char **args)
{
	char	*path;

	if (args[2])
		return (arg_error(shell));
	else if (!args[1] || args[1][0] == '~')
	{
		if (!args[1])
			path = ft_strdup(get_env_var(shell, "HOME"));
		else if (args[1][0] == '~')
			path = ft_strjoin(get_env_var(shell, "HOME"), args[1] + 1);
		if (!path)
			return (home_error(shell));
	}
	else
	{
		path = ft_strdup(args[1]);
		if (!path)
			return (1);
	}
	if (chdir(path) == -1)
		return (path_error(shell, path));
	free(path);
	return (0);
}
