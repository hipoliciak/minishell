/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:02:48 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/26 00:04:55 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	path_error(char *path)
{
	ft_putstr_fd("cd: ", 2);
	perror(path);
	if (path)
		free(path);
	return (1);
}

static int	home_error(void)
{
	ft_putstr_fd("cd: HOME not set\n", 2);
	return (1);
}

int	cd_builtin(t_shell *shell, char **args)
{
	char	*path;

	if (!args[1])
	{
		path = ft_strdup(get_env_var(shell, "HOME"));
		if (!path)
			return (home_error());
	}
	else if (args[1][0] == '~')
	{
		path = ft_strjoin(get_env_var(shell, "HOME"), args[1] + 1);
		if (!path)
			return (home_error());
	}
	else
	{
		path = ft_strdup(args[1]);
		if (!path)
			return (1);
	}
	if (chdir(path) == -1)
		return (path_error(path));
	free(path);
	return (0);
}
