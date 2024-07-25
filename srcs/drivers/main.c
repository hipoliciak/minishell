/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:38:56 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/07/26 00:08:31 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell();
	if (!shell)
		return (1);
	run_shell(shell);
	free_shell(shell);
	return (0);
}
