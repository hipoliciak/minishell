/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 01:59:50 by dkolida           #+#    #+#             */
/*   Updated: 2024/09/05 22:33:21 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_group(t_group *group, int tokens_count);

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

void	free_groups(t_group **pipe_groups, int tokens_count)
{
	int	i;

	i = 0;
	if (!pipe_groups)
		return ;
	while (i < tokens_count)
	{
		if (pipe_groups[i])
		{
			free_group(pipe_groups[i], tokens_count);
			if (pipe_groups[i]->args)
			{
				free(pipe_groups[i]->args);
				pipe_groups[i]->args = NULL;
			}
			free(pipe_groups[i]);
			pipe_groups[i] = NULL;
		}
		i++;
	}
	free(pipe_groups);
}

static void	free_group(t_group *group, int tokens_count)
{
	int	j;

	j = 0;
	if (!group)
		return ;
	while (group->args && j <= tokens_count)
	{
		if (group->args[j] != NULL)
		{
			free(group->args[j]);
			group->args[j] = NULL;
		}
		j++;
	}
	if (group->in_file_name)
	{
		free(group->in_file_name);
		group->in_file_name = NULL;
	}
	if (group->out_file_name)
	{
		free(group->out_file_name);
		group->out_file_name = NULL;
	}
}
