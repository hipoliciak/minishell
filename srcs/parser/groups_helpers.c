/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 01:59:50 by dkolida           #+#    #+#             */
/*   Updated: 2024/09/06 16:17:03 by dkolida          ###   ########.fr       */
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

void	file_out_redir(t_tokenizer *data, t_group *group, int *i)
{
	if (ft_strcmp(data->tokens[(*i) + 1], ">") == 0)
	{
		group->out_file_append = 1;
		(*i)++;
	}
	group->out_file_name = ft_strdup(data->tokens[++(*i)]);
}

int	output_mode(int update_mode)
{
	if (update_mode)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else
		return (O_WRONLY | O_CREAT | O_TRUNC);
}
