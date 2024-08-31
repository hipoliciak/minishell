/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:14:08 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/28 17:35:54 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_shell *shell, char **args)
{
	int	i;

	if (!shell || !shell->env_vars || !args)
		exit(1);
	i = 1;
	while (args[i])
	{
		if (get_env_var(shell, args[i]))
			remove_env_var(shell, args[i]);
		i++;
	}
	shell->last_exit_code = 0;
	return (0);
}
