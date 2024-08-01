/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 22:54:51 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/31 23:36:41 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shell_env_vars(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		set_env_var(shell, "PWD", cwd);
		free(cwd);
	}
	set_env_var(shell, "HOME", getenv("HOME"));
	set_env_var(shell, "USER", getenv("USER"));
	set_env_var(shell, "PATH", getenv("PATH"));
	set_env_var(shell, "EMPTY", "");
}

char	**iter_env_vars(char **env, t_env_var *var)
{
	int		i;
	char	*temp;

	i = 0;
	while (var)
	{
		temp = ft_strjoin(var->key, "=");
		if (!temp)
		{
			ft_free_split(env);
			return (NULL);
		}
		env[i] = ft_strjoin(temp, var->value);
		free(temp);
		if (!env[i])
		{
			ft_free_split(env);
			return (NULL);
		}
		i++;
		var = var->next;
	}
	env[i] = NULL;
	return (env);
}

char	**env_vars_to_env(t_env_var **env_vars)
{
	t_env_var	*var;
	char		**env;
	int			i;

	if (!env_vars)
		return (NULL);
	i = 0;
	var = *env_vars;
	while (var)
	{
		i++;
		var = var->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	var = *env_vars;
	env = iter_env_vars(env, var);
	if (!env)
		return (NULL);
	return (env);
}
