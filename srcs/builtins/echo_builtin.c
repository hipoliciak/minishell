/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:55:21 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/30 01:43:49 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_builtin(t_shell *shell, char **args)
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
		ft_putstr_fd(args[i], shell->out_fd);
		if (args[i + 1])
			ft_putstr_fd(" ", shell->out_fd);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", shell->out_fd);
	shell->last_exit_code = 0;
	return (0);
}
