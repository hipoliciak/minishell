/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:08:49 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/28 17:35:02 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_shell *shell)
{
	t_env_var	*var;

	if (!shell)
		return (1);
	var = *shell->env_vars;
	if (!var)
		return (1);
	while (var)
	{
		print_env_var(var);
		var = var->next;
	}
	shell->last_exit_code = 0;
	return (0);
}
