/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:12:33 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/08/31 17:17:27 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_key_value_pair(char **key_value_pair)
{
	free(key_value_pair[0]);
	free(key_value_pair[1]);
	free(key_value_pair);
}

static char	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!key[i] || (!ft_isalpha(key[i]) && key[i] != '_'))
		return (0);
	i++;
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	**get_key_value_pair(char *arg)
{
	char	**key_value_pair;
	char	*eq_pos;

	key_value_pair = malloc(sizeof(char *) * 3);
	if (!key_value_pair)
		return (NULL);
	eq_pos = ft_strchr(arg, '=');
	if (!eq_pos)
	{
		key_value_pair[0] = ft_strdup(arg);
		key_value_pair[1] = ft_strdup("");
	}
	else
	{
		key_value_pair[0] = ft_substr(arg, 0, eq_pos - arg);
		key_value_pair[1] = ft_substr(eq_pos + 1, 0, ft_strlen(eq_pos));
	}
	key_value_pair[2] = NULL;
	if (!key_value_pair[0] || (eq_pos != NULL && !key_value_pair[1]))
	{
		free_key_value_pair(key_value_pair);
		return (NULL);
	}
	return (key_value_pair);
}

static char	not_valid_identifier(t_shell *shell)
{
	ft_putendl_fd(" not a valid identifier", 2);
	shell->last_exit_code = 1;
	return (1);
}

int	export_builtin(t_shell *shell, char **args)
{
	int		i;
	char	**key_value_pair;

	i = 1;
	while (args[i])
	{
		if (!is_valid_key(args[i]))
			return (not_valid_identifier(shell));
		else if (ft_strchr(args[i], '=') != NULL)
		{
			key_value_pair = get_key_value_pair(args[i]);
			if (!key_value_pair)
				exit(1);
			set_env_var(shell, key_value_pair[0], key_value_pair[1]);
			free_key_value_pair(key_value_pair);
		}
		else
			set_env_var(shell, args[i], "");
		i++;
	}
	shell->last_exit_code = 0;
	return (0);
}
