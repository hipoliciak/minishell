/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:14:08 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/09/05 20:36:36 by dmodrzej         ###   ########.fr       */
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
	free(shell->env);
	shell->env = env_vars_to_env(shell->env_vars);
	if (!shell->env)
		exit(1);
	shell->last_exit_code = 0;
	return (0);
}
