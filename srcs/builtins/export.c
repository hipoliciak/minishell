/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 23:12:33 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/22 21:04:01 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
