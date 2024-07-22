/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:10:29 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/22 23:15:01 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_shell *shell, char **args)
{
	int		i;
	char	*arg;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	if (i == 2)
	{
		arg = args[1];
		while (*arg)
		{
			if (!ft_isdigit(*arg) && *arg != '-' && *arg != '+')
			{
				ft_putendl_fd("exit: numeric argument required", 2);
				return (1);
			}
			arg++;
		}
		shell->exit_code = ft_atoi(args[1]);
	}
	else
		shell->exit_code = 0;
	free_shell(shell);
	exit(shell->exit_code);
	return (2);
}
