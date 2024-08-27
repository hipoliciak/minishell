/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:55:21 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/27 23:05:13 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	echo_builtin(t_shell *shell, char **args)
// {
// 	int	i;
// 	int	nl;

// 	i = 1;
// 	nl = 1;
// 	if (args[i] && !ft_strcmp(args[i], "-n"))
// 	{
// 		nl = 0;
// 		i++;
// 	}
// 	while (args[i])
// 	{
// 		ft_putstr_fd(args[i], STDOUT_FILENO);
// 		if (args[i + 1])
// 			ft_putstr_fd(" ", STDOUT_FILENO);
// 		i++;
// 	}
// 	if (nl)
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// 	shell->last_exit_code = 0;
// 	return (0);
// }

void	echo_builtin(t_shell *shell, char **args)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (args[i] && !ft_strcmp(args[i], "-n"))
	{
		nl = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", STDOUT_FILENO);
	shell->last_exit_code = 0;
}
