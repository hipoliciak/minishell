/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:02:48 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/27 23:19:36 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static char *handle_second_arg(char *path, char **args);

static int	arg_error(void)
{
	ft_putendl_fd(" too many arguments", 2);
	return (1);
}

static int	path_error(char *path)
{
	perror(path);
	if (path)
		free(path);
	return (1);
}

static int	home_error(void)
{
	ft_putendl_fd("cd: HOME not set", 2);
	return (1);
}

int	cd_builtin(t_shell *shell, char **args)
{
	char	*path;

	path = "";
	if (args[2])
		return (arg_error());
	else if (!args[1] || args[1][0] == '~')
	{
		if (!args[1])
			path = ft_strdup(get_env_var(shell, "HOME"));
		else if (args[1][0] == '~')
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
	set_env_var(shell, "PWD", getcwd(NULL, 0));
	free(path);
	return (0);
}

// void	cd_builtin(t_shell *shell, char **args)
// {
// 	char	*path;

// 	path = "";
// 	if (args[3])
// 		shell->last_exit_code = 1;
// 	else if (!args[1] || args[1][0] == '~')
// 	{
// 		if (!args[1])
// 			path = ft_strdup(get_env_var(shell, "HOME"));
// 		else if (args[1][0] == '~')
// 			path = ft_strjoin(get_env_var(shell, "HOME"), args[1] + 1);
// 		if (!path)
// 			shell->last_exit_code = 1;
// 	}
// 	else
// 	{
// 		path = ft_strdup(args[1]);
// 		if (!path)
// 			shell->last_exit_code = 1;
// 	}
// 	if (chdir(path) == -1)
// 	{
// 		ft_putendl_fd(strerror(errno), 2);
// 		shell->last_exit_code = 1;
// 	}
// 	else
// 		set_env_var(shell, "PWD", getcwd(NULL, 0));
// 	free(path);
// }

// void cd_builtin(t_shell *shell, char **args)
// {
//     char *path = NULL;
//     char *old_pwd = NULL;
//     char *new_pwd = NULL;

//     if (args[2])
//     {
//         ft_putendl_fd("cd: too many arguments", 2);
//         shell->last_exit_code = 1;
//         return;
//     }

//     if (!args[1] || ft_strcmp(args[1], "~") == 0)
//     {
//         path = get_env_var(shell, "HOME");
//         if (!path)
//         {
//             ft_putendl_fd("cd: HOME not set", 2);
//             shell->last_exit_code = 1;
//             return;
//         }
//     }
//     else if (args[1][0] == '~')
//     {
//         char *home = get_env_var(shell, "HOME");
//         if (!home)
//         {
//             ft_putendl_fd("cd: HOME not set", 2);
//             shell->last_exit_code = 1;
//             return;
//         }
//         path = ft_strjoin(home, args[1] + 1);
//         if (!path)
//         {
//             ft_putendl_fd("cd: memory allocation error", 2);
//             shell->last_exit_code = 1;
//             return;
//         }
//     }
//     else
//     {
//         path = ft_strdup(args[1]);
//         if (!path)
//         {
//             ft_putendl_fd("cd: memory allocation error", 2);
//             shell->last_exit_code = 1;
//             return;
//         }
//     }

//     old_pwd = getcwd(NULL, 0);
//     if (chdir(path) == -1)
//     {
//         ft_putstr_fd("cd: ", 2);
//         ft_putstr_fd(path, 2);
//         ft_putstr_fd(": ", 2);
//         ft_putendl_fd(strerror(errno), 2);
//         shell->last_exit_code = 1;
//     }
//     else
//     {
//         new_pwd = getcwd(NULL, 0);
//         if (new_pwd)
//         {
//             set_env_var(shell, "OLDPWD", old_pwd);
//             set_env_var(shell, "PWD", new_pwd);
//             shell->last_exit_code = 0;
//         }
//         else
//         {
//             ft_putendl_fd("cd: error getting current directory", 2);
//             shell->last_exit_code = 1;
//         }
//     }

//     free(path);
//     free(old_pwd);
//     free(new_pwd);
// }

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
