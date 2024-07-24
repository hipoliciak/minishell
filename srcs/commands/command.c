/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:40:50 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/24 22:36:56 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_command(t_shell *shell, char *line)
{
	char	**args;
	int		i;
	int		j;
	int		k;
	char	*trimmed;

	i = 0;
	args = ft_split(line, ' ');
	if (!args)
		return (1);
	if (!args[0])
	{
		ft_free_split(args);
		return (0);
	}
	while (args[i])
	{
		j = 0;
		k = 0;
		trimmed = malloc(strlen(args[i]) + 1);
		if (!trimmed)
		{
			ft_free_split(args);
			return (1);
		}
		while (args[i][j])
		{
			if (args[i][j] == '\'' || args[i][j] == '\"')
			{
				j++;
				continue ;
			}
			trimmed[k++] = args[i][j++];
		}
		trimmed[k] = '\0';
		free(args[i]);
		args[i] = trimmed;
		i++;
	}
	exec_builtins(shell, args);
	ft_free_split(args);
	return (0);
}
