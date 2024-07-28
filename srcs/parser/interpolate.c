/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkolida <dkolida@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:47:26 by dkolida           #+#    #+#             */
/*   Updated: 2024/07/28 04:26:48 by dkolida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

char	*data_str(char *str, int *i, t_shell *shell);

static char	*get_var_name(char *str)
{
	char	*var_name;
	int		i;

	i = 0;
	while (str[i] && !ft_strchr(" '\"$", str[i]))
		i++;
	var_name = ft_substr(str, 0, i);
	if (!var_name)
		return (NULL);
	return (var_name);
}

static char	*handle_dollars(t_shell *shell, char *str)
{
	char	*var_name;
	char	*new_str;
	int		i;
	char	*tmp;

	i = 0;
	new_str = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			tmp = data_str(str, &i, shell);
			new_str = ft_strjoin_and_free(new_str, tmp);
		}
		else
			new_str = ft_strjoin_char(new_str, str[i++]);
	}
	free(str);
	return (new_str);
}

void	interpolate(t_shell *shell, t_tokenizer *data)
{
	int	i;

	i = 0;
	while (data->tokens[i])
	{
		if (data->not_interpolate[i])
		{
			i++;
			continue ;
		}
		if (ft_strchr(data->tokens[i], '$'))
			data->tokens[i] = handle_dollars(shell, data->tokens[i]);
		i++;
	}
}

static char	*data_str(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*tmp;

	if (str[*i] == '?')
	{
		tmp = ft_itoa(shell->last_exit_code);
		*i += ft_strlen(tmp);
	}
	else
	{
		var_name = get_var_name(&str[*i]);
		*i += ft_strlen(var_name);
		tmp = ft_strdup(get_env_var(shell, var_name));
		free(var_name);
	}
	return (tmp);
}
