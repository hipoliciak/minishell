/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:14:08 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/24 23:55:01 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_shell *shell, char **args)
{
	int	i;

	if (!shell || !shell->env_vars || !args)
		return (1);
	i = 1;
	while (args[i])
	{
		if (get_env_var(shell, args[i]))
			remove_env_var(shell, args[i]);
		i++;
	}
	return (0);
}
