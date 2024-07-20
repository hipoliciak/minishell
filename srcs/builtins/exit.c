/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:10:29 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/20 23:10:59 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 1)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	if (i == 1)
	{
		if (!ft_isdigit(args[0][0]))
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			return (1);
		}
		shell->exit_code = ft_atoi(args[0]);
	}
	return (2);
}
