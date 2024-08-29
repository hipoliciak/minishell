/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:04:36 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/29 20:52:12 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	return (!ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "exit")
		|| !ft_strcmp(command, "pwd"));
}

int	exec_builtin(t_shell *shell, char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		return (echo_builtin(shell, args));
	else if (!ft_strcmp(args[0], "cd"))
		return (cd_builtin(shell, args));
	else if (!ft_strcmp(args[0], "env"))
		return (env_builtin(shell));
	else if (!ft_strcmp(args[0], "export"))
		return (export_builtin(shell, args));
	else if (!ft_strcmp(args[0], "unset"))
		return (unset_builtin(shell, args));
	else if (!ft_strcmp(args[0], "exit"))
		return (exit_builtin(shell, args));
	else if (!ft_strcmp(args[0], "pwd"))
		return (pwd_builtin(shell));
	shell->last_exit_code = 127;
	return (shell->last_exit_code);
}

void	exec_command(t_shell *shell, char **args)
{
	int	builtin;
	int	i;

	i = 0;
	while (args[i])
	{
		builtin = is_builtin(args[i]);
		if (builtin)
		{
			if (exec_builtin(shell, shell->groups[shell->group_i]->args) != 0)
				exit(shell->last_exit_code);
			return ;
		}
		if (execve_path(shell, shell->groups[shell->group_i]->args) != 0)
		{
			shell->last_exit_code = 127;
			exit(shell->last_exit_code);
		}
		i++;
	}
}
