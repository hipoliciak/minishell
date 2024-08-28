/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:04:36 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/28 19:05:34 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
