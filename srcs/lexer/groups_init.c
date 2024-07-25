/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:22:09 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/25 02:42:44 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_group	*group_init(char *group);
static void		extract_infile(t_group *group);

t_group	**group_input(char *line)
{
	t_group	**groups;
	char	**str_groups;
	int		group_count;
	int		i;

	str_groups = ft_split(line, '|');
	if (!str_groups)
		return (NULL);
	group_count = 0;
	while (str_groups[group_count])
		group_count++;
	groups = malloc(sizeof(t_group *) * (group_count + 1));
	if (!groups)
		return (NULL);
	i = 0;
	while (str_groups[i])
	{
		if (*str_groups[i] != '\0')
			groups[i] = group_init(str_groups[i]);
		i++;
	}
	groups[i] = NULL;
	free(str_groups);
	return (groups);
}

static t_group	*group_init(char *group)
{
	t_group	*new_group;

	if (!group)
		return (NULL);
	new_group = malloc(sizeof(t_group));
	if (!new_group)
		return (NULL);
	new_group->str = group;
	new_group->in_file_name = NULL;
	extract_infile(new_group);
	new_group->out_file_name = NULL;
	return (new_group);
}

static void	extract_infile(t_group *group)
{
	char	*filename;
	char	**split_group;
	char	*tmp;

	tmp = group->str;
	filename = ft_strchr(group->str, '<');
	if (filename == NULL)
		return ;
	split_group = ft_split(++filename, ' ');
	if (!split_group)
		return ;
	if (split_group[0])
	{
		group->in_file_name = ft_strdup(split_group[0]);
		if (!group->in_file_name)
			return ;
		while (*filename == ' ')
			filename++;
		group->str = ft_strdup(filename + ft_strlen(group->in_file_name));
		free(tmp);
	}
	else
		perror("Error: parse error near '<'");
	ft_free_split(split_group);
}

char	*char_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (str == NULL)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*ft_strjoin_char(char *s1, char c)
{
	char	*c_str;
	char	*new_str;

	c_str = char_to_str(c);
	if (!c_str)
		return (NULL);
	new_str = ft_strjoin(s1, c_str);
	free(c_str);
	return (new_str);
}

char	**tokenize(char *input)
{
	char	**tokens;
	char	*current_token;
	int		in_double_quotes;
	int		in_single_quotes;
	int		i;
	int		t;

	tokens = malloc(sizeof(char *) * (ft_strlen(input) + 1));
	if (!tokens)
		return (NULL);
	current_token = ft_strdup("");
	in_double_quotes = 0;
	in_single_quotes = 0;
	i = 0;
	t = 0;
	while (input[i])
	{
		if (input[i] == ' ' && !in_double_quotes && !in_single_quotes)
		{
			if (*current_token != '\0')
			{
				tokens[t++] = current_token;
				current_token = ft_strdup("");
			}
		}
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (input[i] == '"')
			{
				if (in_single_quotes)
					current_token = ft_strjoin_char(current_token, input[i]);
				else
				{
					if (in_double_quotes)
					{
						tokens[t++] = current_token;
						current_token = ft_strdup("");
					}
					in_double_quotes = !in_double_quotes;
				}
			}
			else
			{
				if (in_double_quotes)
					current_token = ft_strjoin_char(current_token, input[i]);
				else
				{
					if (in_single_quotes)
					{
						tokens[t++] = current_token;
						current_token = ft_strdup("");
					}
					in_single_quotes = !in_single_quotes;
				}
			}
		}
		else if ((input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == ';') && !in_double_quotes && !in_single_quotes)
		{
			if (*current_token != '\0')
			{
				tokens[t++] = current_token;
				current_token = ft_strdup("");
			}
			if (ft_isprint(input[i]))
				tokens[t++] = char_to_str(input[i]);
		}
		else
			current_token = ft_strjoin_char(current_token, input[i]);
		i++;
	}
	if (*current_token != '\0')
		tokens[t++] = current_token;
	tokens[t] = NULL;
	if (in_double_quotes || in_single_quotes)
	{
		ft_free_split(tokens);
		tokens = NULL;
		perror("Error: unclosed quotes");
	}
	return (tokens);
}
