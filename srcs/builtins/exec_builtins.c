/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:04:36 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/24 22:57:45 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_shell *shell, char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		return (echo_builtin(shell, args));
	if (!ft_strcmp(args[0], "cd"))
		return (cd_builtin(shell, args));
	if (!ft_strcmp(args[0], "env"))
		return (env_builtin(shell));
	if (!ft_strcmp(args[0], "export"))
		return (export_builtin(shell, args));
	if (!ft_strcmp(args[0], "unset"))
		return (unset_builtin(shell, args));
	if (!ft_strcmp(args[0], "exit"))
		return (exit_builtin(shell, args));
	if (!ft_strcmp(args[0], "pwd"))
		return (pwd_builtin(shell));
	ft_free_split(args);
	return (0);
}
