/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 01:59:50 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/22 02:05:56 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_groups(t_group **groups)
{
	int	i;

	i = 0;
	while (groups[i])
	{
		printf("group %d: %s\n", i, groups[i]->str);
		i++;
	}
}

void	free_groups(t_group **pipe_groups)
{
	int	i;

	i = 0;
	while (pipe_groups[i])
	{
		if (pipe_groups[i]->in_file_name != NULL)
			free(pipe_groups[i]->in_file_name);
		free(pipe_groups[i]->str);
		free(pipe_groups[i]);
		i++;
	}
	free(pipe_groups);
}
