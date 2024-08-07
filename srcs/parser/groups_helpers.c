/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 01:59:50 by dkolida           #+#    #+#             */
/*   Updated: 2024/08/07 16:29:42 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_groups(t_group **groups)
{
	int	i;
	int	j;

	i = 0;
	while (groups[i])
	{
		j = 0;
		printf("group %d:", i);
		while (j < groups[i]->arg_i)
		{
			printf("%s ", groups[i]->args[j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	free_groups(t_group **pipe_groups)
{
	int	i;

	if (!pipe_groups)
		return ;
	i = 0;
	while (pipe_groups[i])
	{
		if (pipe_groups[i]->args)
		{
			while (pipe_groups[i]->arg_i--)
				free(pipe_groups[i]->args[pipe_groups[i]->arg_i]);
			free(pipe_groups[i]->args);
		}
		if (pipe_groups[i]->in_file_name)
			free(pipe_groups[i]->in_file_name);
		free(pipe_groups[i]);
		i++;
	}
	free(pipe_groups);
}
