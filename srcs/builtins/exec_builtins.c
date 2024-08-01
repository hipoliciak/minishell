/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:04:36 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/26 01:33:20 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_shell *shell, char **args)
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
	else
		printf("minishell: %s: command not found\n", args[0]);
	return (0);
}
