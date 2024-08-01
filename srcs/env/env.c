/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:15:47 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/31 22:57:33 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_env_var(t_shell *shell, char *key, char *value)
{
	t_env_var	*new;

	if (!shell || !key || !value)
		return (1);
	new = new_env_var(key, value);
	if (!new)
		return (1);
	if (get_env_var(shell, key))
		remove_env_var(shell, key);
	add_env_var(shell->env_vars, new);
	return (0);
}

char	*get_env_var(t_shell *shell, char *key)
{
	t_env_var	*var;

	if (!shell || !shell->env_vars || !key)
		return (NULL);
	var = *shell->env_vars;
	while (var)
	{
		if (ft_strcmp(var->key, key) == 0)
			return (var->value);
		var = var->next;
	}
	return (NULL);
}

void	remove_env_var(t_shell *shell, char *key)
{
	t_env_var	*var;
	t_env_var	*prev;

	if (!shell || !shell->env_vars || !key)
		return ;
	var = *shell->env_vars;
	prev = NULL;
	while (var)
	{
		if (ft_strcmp(var->key, key) == 0)
		{
			if (prev)
				prev->next = var->next;
			else
				*shell->env_vars = var->next;
			free(var->key);
			free(var->value);
			free(var);
			return ;
		}
		prev = var;
		var = var->next;
	}
}

void	print_env_var(t_env_var *var)
{
	if (!var)
		return ;
	printf("%s=%s\n", var->key, var->value);
}
