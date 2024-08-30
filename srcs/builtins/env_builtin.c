/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:08:49 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/30 03:31:50 by dkolida          ###   ########.fr       */
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
		if (var)
		{
			ft_putstr_fd(var->key, shell->out_fd);
			ft_putstr_fd("=", shell->out_fd);
			ft_putendl_fd(var->value, shell->out_fd);
		}
		var = var->next;
	}
	shell->last_exit_code = 0;
	return (0);
}
