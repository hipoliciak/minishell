/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:22:09 by dkolida           #+#    #+#             */
/*   Updated: 2024/08/07 16:31:16 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_group	*group_init(int argc);
//static void		extract_infile(t_group *group);
int		add_to_group(t_shell *shell, t_group *group, char *token, int is_end);
int		shell_groups_init(t_shell *shell, char **tokens);
void	set_group_infile_name(t_group *group, char *token);

void	group_input(t_shell *shell, char **tokens)
{
	t_group	*group;
	int		tokens_c;
	int		i;

	tokens_c = shell_groups_init(shell, tokens);
	i = 0;
	group = NULL;
	while (tokens[i])
	{
		if (!group)
		{
			group = group_init(tokens_c);
			if (!group)
				return ;
		}
		if (ft_strcmp(tokens[i], "<") == 0)
		{
			set_group_infile_name(group, tokens[++i]);
			if ( i == tokens_c - 1)
			{
				shell->groups[shell->group_i++] = group;
				break ;
			}
		}

		if (add_to_group(shell, group, tokens[i], i == tokens_c - 1))
		{
			group = NULL;
		}

		i++;
	}
}

int	add_to_group(t_shell *shell, t_group *group, char *token, int is_end)
{
	if (ft_strcmp(token, "|") == 0 || is_end)
	{
		if (is_end && ft_strcmp(token, "|") != 0)
		{
			group->args[group->arg_i++] = ft_strdup(token);
			if (group->args[group->arg_i - 1] == NULL)
			{
				printf("Error: malloc failed\n");
			}
		}
		shell->groups[shell->group_i++] = group;
		return (1);
	}
	else
	{
		group->args[group->arg_i++] = ft_strdup(token);
		if (group->args[group->arg_i - 1] == NULL)
		{
			printf("Error: malloc failed\n");
		}
	}
	return (0);
}

t_group	*group_init(int argc)
{
	t_group	*group;

	group = malloc(sizeof(t_group));
	if (!group)
		return (NULL);
	group->args = malloc(sizeof(char *) * (argc + 1));
	if (!group->args)
	{
		free(group);
		return (NULL);
	}
	while (group->args[argc--])
		group->args[argc] = NULL;
	group->arg_i = 0;
	group->in_file_name = NULL;
	group->out_file_name = NULL;
	return (group);
}

int	shell_groups_init(t_shell *shell, char **tokens)
{
	int	tokens_count;
	int i;

	tokens_count = 0;
	while (tokens[tokens_count])
		tokens_count++;
	shell->groups = malloc(sizeof(t_group *) * (tokens_count + 1));
	if (!shell->groups)
		return (0);
	shell->group_i = 0;
	i = 0;
	while (i < tokens_count)
		shell->groups[i++] = NULL;
	return (tokens_count);
}

void	set_group_infile_name(t_group *group, char *token)
{
	group->in_file_name = ft_strdup(token);
	if (!group->in_file_name)
	{
		printf("Error: malloc failed\n");
	}
}
