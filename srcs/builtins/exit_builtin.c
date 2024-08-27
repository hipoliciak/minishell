/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:10:29 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/27 23:25:40 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	too_many_args_error(t_shell *shell)
{
	ft_putendl_fd("exit: too many arguments", 2);
	shell->last_exit_code = 1;
	return (1);
}

static int	number_error(t_shell *shell)
{
	ft_putendl_fd("exit: numeric argument required", 2);
	shell->last_exit_code = 2;
	return (2);
}

int	exit_builtin(t_shell *shell, char **args)
{
	int		i;
	char	*arg;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
		return (too_many_args_error(shell));
	if (i == 2)
	{
		arg = args[1];
		while (*arg)
		{
			if (!ft_isdigit(*arg) && *arg != '-' && *arg != '+')
				return (number_error(shell));
			arg++;
		}
		shell->last_exit_code = ft_atoi(args[1]);
	}
	else
		shell->last_exit_code = 0;
	exit(shell->last_exit_code);
	return (2);
}

// void	exit_builtin(t_shell *shell, char **args)
// {
// 	int		i;
// 	char	*arg;

// 	i = 0;
// 	while (args[i])
// 		i++;
// 	if (i > 2)
// 	{
// 		ft_putendl_fd("exit: too many arguments", 2);
// 		shell->last_exit_code = 1;
// 	}
// 	else if (i == 2)
// 	{
// 		arg = args[1];
// 		while (*arg)
// 		{
// 			if (!ft_isdigit(*arg) && *arg != '-' && *arg != '+')
// 			{
// 				ft_putendl_fd("exit: numeric argument required", 2);
// 				shell->last_exit_code = 2;
// 				exit(2);
// 			}
// 			arg++;
// 		}
// 		shell->last_exit_code = ft_atoi(args[1]);
// 	}
// 	else
// 		shell->last_exit_code = 0;
// 	exit(shell->last_exit_code);
// }
