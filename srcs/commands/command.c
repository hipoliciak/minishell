/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:40:50 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/25 23:32:44 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_command(t_shell *shell, char *line)
{
	char	**args;

	args = ft_split(line, ' ');
	if (!args)
		return (1);
	if (!args[0])
	{
		ft_free_split(args);
		return (0);
	}
	exec_builtins(shell, args);
	ft_free_split(args);
	return (0);
}
