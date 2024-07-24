/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:55:21 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/25 00:36:11 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	identify_variable(t_shell *shell, char *str)
{
	char	*var_name;

	while (*str && *str != ' ' && *str != '$')
		str++;
	*str = '\0';
	var_name = ft_strdup(str);
	if (!var_name)
		return ;
	ft_putstr_fd(get_env_var(shell, var_name), 1);
	free(var_name);
}

static void	handle_dollars(t_shell *shell, char *str)
{
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			if (*str == '?')
			{
				ft_putstr_fd(ft_itoa(shell->last_exit_code), 1);
				str++;
			}
			else
				identify_variable(shell, str);
		}
		else
		{
			ft_putchar_fd(*str, 1);
			str++;
		}
	}
}

int	echo_builtin(t_shell *shell, char **args)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (args[i] && !ft_strcmp(args[i], "-n"))
	{
		nl = 0;
		i++;
	}
	while (args[i])
	{
		handle_dollars(shell, args[i]);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (nl)
		ft_putstr_fd("\n", 1);
	(void)shell;
	shell->last_exit_code = 0;
	return (0);
}
