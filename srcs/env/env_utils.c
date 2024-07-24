/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 22:08:33 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/25 00:40:11 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*new_env_var(char *key, char *value)
{
	t_env_var	*var;

	var = malloc(sizeof(t_env_var));
	if (!var)
		return (NULL);
	var->key = ft_strdup(key);
	if (!var->key)
	{
		free(var);
		return (NULL);
	}
	var->value = ft_strdup(value);
	if (!var->value)
	{
		free(var->key);
		free(var);
		return (NULL);
	}
	var->next = NULL;
	return (var);
}

void	add_env_var(t_env_var **env_vars, t_env_var *new)
{
	t_env_var	*last;

	if (!new)
		return ;
	if (!*env_vars)
	{
		*env_vars = new;
		return ;
	}
	last = last_env_var(*env_vars);
	last->next = new;
}

t_env_var	*last_env_var(t_env_var *var)
{
	if (!var)
		return (NULL);
	while (var->next)
		var = var->next;
	return (var);
}

void	free_env_var(t_env_var *var)
{
	if (!var)
		return ;
	free(var->key);
	free(var->value);
	free_env_var(var->next);
	free(var);
}

void	free_all_env_vars(t_env_var **env_vars)
{
	while (*env_vars)
	{
		free_env_var(*env_vars);
		*env_vars = (*env_vars)->next;
	}
	free(*env_vars);
}
