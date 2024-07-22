/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:08:49 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/22 23:41:00 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char **env, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, len) && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

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

int	builtin_env(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_putendl_fd(shell->env[i], 1);
		i++;
	}
	(void)args;
	return (0);
}
