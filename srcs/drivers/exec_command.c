/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:04:36 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/27 23:54:27 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	exec_command(t_shell *shell, char **args)
// {
// 	if (!ft_strcmp(args[0], "echo"))
// 		return (echo_builtin(shell, args));
// 	else if (!ft_strcmp(args[0], "cd"))
// 		return (cd_builtin(shell, args));
// 	else if (!ft_strcmp(args[0], "env"))
// 		return (env_builtin(shell));
// 	else if (!ft_strcmp(args[0], "export"))
// 		return (export_builtin(shell, args));
// 	else if (!ft_strcmp(args[0], "unset"))
// 		return (unset_builtin(shell, args));
// 	else if (!ft_strcmp(args[0], "exit"))
// 		return (exit_builtin(shell, args));
// 	else if (!ft_strcmp(args[0], "pwd"))
// 		return (pwd_builtin(shell));
// 	else if (execve_path(shell, args) == 1)
// 	{
// 		shell->last_exit_code = 127;
// 		return (127);
// 	}
// 	return (0);
// }

int	is_builtin(char *command)
{
	int		is_builtin;

	is_builtin = 0;
	if (!ft_strcmp(command, "echo"))
		is_builtin = 1;
	else if (!ft_strcmp(command, "cd"))
		is_builtin = 1;
	else if (!ft_strcmp(command, "env"))
		is_builtin = 1;
	else if (!ft_strcmp(command, "export"))
		is_builtin = 1;
	else if (!ft_strcmp(command, "unset"))
		is_builtin = 1;
	else if (!ft_strcmp(command, "exit"))
		is_builtin = 1;
	else if (!ft_strcmp(command, "pwd"))
		is_builtin = 1;
	return (is_builtin);
}

void	exec_command(t_shell *shell, char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		echo_builtin(shell, args);
	else if (!ft_strcmp(args[0], "cd"))
	{
		if (cd_builtin(shell, args) == 1)
			shell->last_exit_code = 1;
	}
	else if (!ft_strcmp(args[0], "env"))
		env_builtin(shell);
	else if (!ft_strcmp(args[0], "export"))
		export_builtin(shell, args);
	else if (!ft_strcmp(args[0], "unset"))
		unset_builtin(shell, args);
	else if (!ft_strcmp(args[0], "exit"))
	{
		if (exit_builtin(shell, args) == 1)
			shell->last_exit_code = 1;
	}
	else if (!ft_strcmp(args[0], "pwd"))
		pwd_builtin(shell);
	else if (execve_path(shell, args) == 1)
		shell->last_exit_code = 127;
}

// if you want to run minishell_tester without getting stuck, comment out 83-84 