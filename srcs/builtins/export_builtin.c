/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:12:33 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/25 00:28:31 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
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
	char	*eq_sign_pos;

	key_value_pair = malloc(sizeof(char *) * 3);
	if (!key_value_pair)
		return (NULL);
	eq_sign_pos = ft_strchr(arg, '=');
	key_value_pair[0] = ft_substr(arg, 0, eq_sign_pos - arg);
	key_value_pair[1] = ft_substr(eq_sign_pos + 1, 0, ft_strlen(eq_sign_pos));
	key_value_pair[2] = NULL;
	return (key_value_pair);
}

int	export_builtin(t_shell *shell, char **args)
{
	int		i;
	char	**key_value_pair;

	i = 1;
	while (args[i])
	{
		if (!is_valid_key(args[i]))
		{
			printf("export: `%s' is not a valid identifier\n", args[i]);
			return (1);
		}
		key_value_pair = get_key_value_pair(args[i]);
		if (!key_value_pair)
			return (1);
		set_env_var(shell, key_value_pair[0], key_value_pair[1]);
		free(key_value_pair[0]);
		free(key_value_pair[1]);
		free(key_value_pair);
		i++;
	}
	return (0);
}
