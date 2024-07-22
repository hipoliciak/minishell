/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:04:36 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/22 23:42:46 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_shell *shell, char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		return (builtin_echo(shell, args));
	else if (!ft_strcmp(args[0], "cd"))
		return (builtin_cd(shell, args));
	else if (!ft_strcmp(args[0], "pwd"))
		return (builtin_pwd(shell, args));
	else if (!ft_strcmp(args[0], "export"))
		return (builtin_export(shell, args));
	else if (!ft_strcmp(args[0], "unset"))
		return (builtin_unset(shell, args));
	else if (!ft_strcmp(args[0], "env"))
		return (builtin_env(shell, args));
	else if (!ft_strcmp(args[0], "exit"))
		return (builtin_exit(shell, args));
	ft_free_split(args);
	return (0);
}
