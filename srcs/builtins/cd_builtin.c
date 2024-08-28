/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:02:48 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/28 18:56:27 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static char *handle_second_arg(char *path, char **args);

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

static char	*set_cd_path(t_shell *shell, char **args)
{
	char	*path;

	path = NULL;
	if (!args[1] || args[1][0] == '~')
	{
		if (!args[1])
			path = ft_strdup(get_env_var(shell, "HOME"));
		else if (args[1][0] == '~')
			path = ft_strjoin(get_env_var(shell, "HOME"), args[1] + 1);
	}
	else
		path = ft_strdup(args[1]);
	return (path);
}

int	cd_builtin(t_shell *shell, char **args)
{
	char	*path;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (args[2])
		return (arg_error(shell));
	path = set_cd_path(shell, args);
	if (!path)
		return (1);
	if (chdir(path) == -1)
		return (path_error(shell, path));
	set_env_var(shell, "OLDPWD", old_pwd);
	set_env_var(shell, "PWD", getcwd(NULL, 0));
	free(path);
	return (0);
}

// // test in your terminal how command "cd $PWD {sone existing dir name}" works
// // if you agree add this function rigth after line 58 (chaking for path)
// /*
// static char *handle_second_arg(char *path, char **args)
// {
// 	if (args[2])
// 		path = ft_strjoin_and_free(path, ft_strjoin("/", args[2]));
// 	return (path);
// }
// */
