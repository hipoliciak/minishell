/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:12:33 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/20 23:40:53 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_env(t_shell *shell, char *key, char *value)
{
	int		i;
	char	*new_env_var;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, ft_strlen(key)) == 0)
		{
			free(shell->env[i]);
			new_env_var = ft_strjoin(key, "=");
			if (!new_env_var)
				return (1);
			shell->env[i] = ft_strjoin(new_env_var, value);
			free(new_env_var);
			if (!shell->env[i])
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	builtin_export(t_shell *shell, char **args)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (args[i])
	{
		key = ft_strdup(args[i]);
		if (!key)
			return (1);
		value = ft_strchr(args[i], '=');
		if (value)
			value++;
		if (value)
			set_env(shell, key, value);
		else
			set_env(shell, key, "");
		free(key);
		i++;
	}
	return (0);
}
